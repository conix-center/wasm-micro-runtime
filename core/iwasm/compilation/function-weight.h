// 15-745 S16 Assignment 1: FunctionWeight.cpp
// Group: Arjun Ramesh (arjunr2) and Nishanth Subramanian (nsubram2)
////////////////////////////////////////////////////////////////////////////////

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/ADT/PostOrderIterator.h"


#include "Dataflow.h" //#include "support.h"
#include <iostream>

using namespace llvm;
using namespace std;

namespace llvm {
  std::map<Function*, uint32_t> fn_straight_line_weight;
  
  LoopInfo* LI;

  /* Globals used for weighted checkpoint */
  struct LoopInfoS {
    uint32_t weight;
    bool checkpointed;
  };
  std::map<BasicBlock*, bool> processed_blocks;
  std::map<Loop*, LoopInfoS> loop_info;
  std::vector<string> instrumented_var_names_str;
  /* */

  uint32_t getInstructionWeight(Instruction* I) {
    uint32_t weight = 0;
    unsigned opcode = I->getOpcode();
    Type* type = I->getType();
    //outs() << "Inst weight: " << *I << "\n";
    switch(opcode) {
      /* Integer Arithmetic */
      case Instruction::Add:
      case Instruction::Sub: weight = 1; break;

      case Instruction::Mul: weight = 4; break;

      case Instruction::UDiv:
      case Instruction::SDiv:
      case Instruction::URem:
      case Instruction::SRem: weight = 25; break;

      /* FP Arithmetic */
      case Instruction::FAdd:
      case Instruction::FSub: weight = 3; break;

      case Instruction::FMul: weight = 4; break;

      case Instruction::FDiv:
      case Instruction::FRem: weight = 25; break; 

      /* Logical Arithmetic */
      case Instruction::Shl:
      case Instruction::LShr:
      case Instruction::AShr: weight = 1; break;

      case Instruction::And:
      case Instruction::Or:
      case Instruction::Xor: weight = 1; break;

      /* Memory Operators */
      //case Alloca:
      case Instruction::Load:
      case Instruction::Store: weight = 3; break;

      case Instruction::AtomicRMW:
      case Instruction::AtomicCmpXchg: weight = 7; break;

      //case Fence
      case Instruction::GetElementPtr: weight = 2; break;


      /* Control-flow operations */
      case Instruction::Ret:
      case Instruction::Br:
      case Instruction::IndirectBr:
      case Instruction::CallBr:
      case Instruction::Invoke: weight = 2; break;


      /* Others */
      case Instruction::ICmp:
      case Instruction::FCmp: weight = 1; break;
      case Instruction::Call: {
        if (CallInst *CI = dyn_cast<CallInst>(I)) {
          Function* fun = CI->getCalledFunction();
          // Indirect call: Const val
          if (!fun) {
            //outs() << "Indirect call!\n";
            weight = 10000;
          }
          else {
            // External function: Const val
            if (fun->isDeclaration()) {
              //outs() << "Declaration fn\n";
              weight = 10000;
            }
            // Direct call: Lookup map
            else { 
              //outs() << "Direct call!\n";
              weight = fn_straight_line_weight[fun];
            }
          }
        }
        break;
      }

      default: weight = 0;
    }

    return weight;
  }




  class FunctionWeight : public ModulePass {
  public:
    static char ID;
    FunctionWeight() : ModulePass(ID) { }
    ~FunctionWeight() { }


    // We don't modify the program, so we preserve all analyses
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
      AU.addRequired<LoopInfoWrapperPass>();
    }


    static uint32_t transfer_fn(Value *V, uint32_t in)
    {
      BasicBlock *B = dyn_cast<BasicBlock>(V);
      // Ignore blocks in Loop (null for blocks_)
      if (LI->getLoopFor(B)) {
        return in;
      }
      // Compute straight-line weight
      else {
        uint32_t weight = 0;
        for (auto &I : *B) {
          // Weight instructions appropriately...
          weight += getInstructionWeight(&I);
        }
        return in + weight;
      }
    }

    // Here, Meet is Max
    static uint32_t meet(std::vector<uint32_t> ins)
    {
      uint32_t max = *std::max_element(ins.begin(), ins.end());
      return max;
    }

    // Print output for each function
    bool runOnModule(Module &M) override {
      CallGraph CG = CallGraph(M);
      for (auto node = po_begin(&CG); node != po_end(&CG); ++node) {
        if (Function* F = node->getFunction()) {
          //outs() << "Found function: " << F->getName() << "\n";
          if (!F->isDeclaration()) {
            // Run loop info pass
            fn_straight_line_weight[F] = 0;
            LI = &getAnalysis<LoopInfoWrapperPass>(*F).getLoopInfo();

            // Run dataflow
            DataflowAnalysis<uint32_t> problem;
            uint32_t top = 0;
            uint32_t entry = 0;
            problem.set(&transfer_fn, &meet, entry, top);
            problem.run_iterations(*F, FORWARDS, BASIC_BLOCKS);

            std::vector<uint32_t> exit_blocks_weight;
            for (auto &BB : *F) {
              Instruction* I = BB.getTerminator();
              if (ReturnInst *RI = dyn_cast<ReturnInst>(I)) {
                uint32_t bw = problem.get_outs(&BB, BASIC_BLOCKS);
                exit_blocks_weight.push_back(bw);
              }
            }

            uint32_t out_weight = *std::max_element(exit_blocks_weight.begin(), exit_blocks_weight.end());
            fn_straight_line_weight[F] = out_weight;
          }
          // Declaration (external-function): set some constant weight
          else {
          }
        }
      }

      outs() << "\nEnd of Module Pass\n";
      clear_instrumentation_vars();

      return false;
    }

    void clear_instrumentation_vars() { 
      instrumented_var_names_str.clear(); 
      processed_blocks.clear();
      loop_info.clear();
      outs() << "Cleared vars for instrumentation\n";
    }
  };
}

// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
char FunctionWeight::ID = 0;
static RegisterPass<FunctionWeight> function_weight("function-weight", "15745: Function Weight Information(excluding loops)", false, false);
