// 15-745 Assignment 2: available.cpp
// Group: Nishanth Subramanian (nsubram2) and Arjun Ramesh (arjunr2)
////////////////////////////////////////////////////////////////////////////////

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/ValueTracking.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Alignment.h"
#include "llvm/Transforms/Utils.h"

#include "Dataflow.h"
#include "function-weight.h"
#include "Global.h"

using namespace llvm;
using namespace std;


namespace
{
  static cl::opt<uint32_t> Threshold("threshold", cl::desc("Threshold for checkpointing"), cl::init(30));

  struct LoopInfoS {
    uint32_t weight;
    bool checkpointed;
  };

  std::map<BasicBlock*, bool> processed_blocks;
  std::vector<Value *> universal_blocks;
  std::map<Loop*, LoopInfoS> loop_info;

  LoopInfo* LICP;
  Loop* current_loop;
  unsigned current_loop_depth;
  Module* current_module;

  class WeightedCheckpoint : public LoopPass
  {

  public:

    static char ID;
    WeightedCheckpoint() : LoopPass(ID) {}

    DataflowAnalysis<uint32_t> problem;

    static uint32_t transfer_fn(Value *V, uint32_t in)
    {
      BasicBlock* B = dyn_cast<BasicBlock>(V);
      if (LICP->getLoopFor(B) != current_loop) {
        return in;
      }
      else {
        uint32_t weight = 0;
        for (auto &I : *B) {
          // Weight instructions appropriately...
          weight += getInstructionWeight(&I);
        }
        return in + weight;
      }
    }

    // Here, Meet is Union operator (OR)
    static uint32_t meet(std::vector<uint32_t> ins)
    {
      uint32_t max = *max_element(ins.begin(), ins.end());
      return max;
    }


    virtual bool doInitialization(Loop* L, LPPassManager &LPM) {
      //outs() << "-------------------\n";
      //outs() << getPassName().str() << " : " << L << "\n";
      //outs() << "-------------------\n";
      string fn_name = L->getHeader()->getParent()->getName().str();
      return false;
    }



    virtual bool runOnLoop(Loop* L, LPPassManager &LPM)
    {

      // Initialization
      current_loop = L;
      current_loop_depth = L->getLoopDepth();
      current_module = L->getHeader()->getModule();
      LICP = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();

      uint32_t top = 0;
      uint32_t entry = 0;
      outs() << "Loop Name: " << L->getName().str() << "\n";
      problem.set(&transfer_fn, &meet, entry, top);
      problem.run_iterations_loop(L, LICP, FORWARDS, BASIC_BLOCKS);

      universal_blocks.clear();
      for (auto &BB : L->blocks()) {
        // If block has not been processed, add
        if (processed_blocks.find(BB) == processed_blocks.end()) {
          processed_blocks[BB] = true;
          universal_blocks.push_back(BB);
        }
      }
      
      /*outs() << "\nIR:\n";
      for (auto &BB : universal_blocks) {
        outs() << *BB << "\n";
        outs() << "<----- " << problem.get_outs(BB, BASIC_BLOCKS) << " ---->\n";
      }*/

      // Works because loop-simplified LL
      BasicBlock* latch = L->getLoopLatch();
      uint32_t loop_weight = problem.get_outs(latch, BASIC_BLOCKS);

      // Add weights of all non-checkpointed loops inside
      for (auto const &subL : L->getSubLoops()) {
        // If next-level loops are not checkpointed, add their weight
        if ((subL->getParentLoop() == L) && !loop_info[subL].checkpointed)
          loop_weight += loop_info[subL].weight;
      }
      loop_info[L].weight = loop_weight;
      loop_info[L].checkpointed = false;
        

      string prefix = "rtloop";
      string fn_name = L->getHeader()->getParent()->getName().str();
      string loop_name = L->getName().str();
      string var_name = prefix + "_" + fn_name + "_" + loop_name;

      // Checkpoint above threshold
      uint32_t THRESHOLD = Threshold;
      outs() << "Loop: " << loop_name << " | Weight/Thresh: " << loop_weight << "/" << THRESHOLD;
      if (loop_weight > THRESHOLD) {
        loop_info[L].checkpointed = true;
        outs() << " ==> Inserting Checkpoint: \'" << var_name << "\'\n";
        Type* int64_type = Type::getInt64Ty(current_module->getContext());
        GlobalVariable* global_cnt = 
            create_int_global(int64_type, var_name, current_module);

        if (global_cnt == nullptr) {
          errs() << "Global already exists!\n";
        }
        Constant* one = ConstantInt::get(int64_type, 1);
        
        Instruction* Inst = L->getHeader()->getFirstNonPHI();
        IRBuilder<> Builder(Inst);
        //LoadInst* li = Builder.CreateLoad(int64_type, global_cnt, true, ".lpchk.ld");
        //Value* inc = Builder.CreateAdd(li, one, ".lpchk.add");
        //StoreInst* si = Builder.CreateStore(inc, global_cnt);
        AtomicRMWInst* ai = Builder.CreateAtomicRMW(AtomicRMWInst::Add, global_cnt, one, MaybeAlign(), AtomicOrdering::AcquireRelease);
      }
      else {
        outs() << "\n";
      }
      // Modifies the incoming Function.
      return true;
    }

    virtual bool doFinalization() {
      outs() << "Completed Pass!\n";
      return false;
    }

    virtual void getAnalysisUsage(AnalysisUsage &AU) const
    {
      AU.setPreservesAll();
      AU.addRequiredTransitive<FunctionWeight>();
      AU.addRequired<LoopInfoWrapperPass>();
    }

    const DataflowAnalysis<uint32_t> &getWeightedCheckpointResult() const { return problem; }
    DataflowAnalysis<uint32_t> &getWeightedCheckpointResult() { return problem; }

  };

  char WeightedCheckpoint::ID = 0;
  RegisterPass<WeightedCheckpoint> weighted_checkpoint("weighted-checkpoint",
                                       "Loop WeightedCheckpointing Pass");
}

