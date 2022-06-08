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


namespace llvm
{

  std::vector<Value *> universal_blocks;
  LoopInfo* LICP;
  Loop* current_loop;
  unsigned current_loop_depth;
  Module* current_module;

  class InsertCheckpoint : public LoopPass
  {

  public:

    static char ID;
    InsertCheckpoint() : LoopPass(ID) {}

    DataflowAnalysis<uint32_t> problem;

    virtual bool doInitialization(Loop* L, LPPassManager &LPM) {
      //outs() << "-------------------\n";
      //outs() << getPassName().str() << " : " << L << "\n";
      //outs() << "-------------------\n";
      string fn_name = L->getHeader()->getParent()->getName().str();
      return false;
    }



    virtual bool runOnLoop(Loop* L, LPPassManager &LPM)
    {

      // Modifies the incoming Function.
      return true;
    }

    virtual bool doFinalization() {
      return false;
    }

    virtual void getAnalysisUsage(AnalysisUsage &AU) const
    {
      AU.setPreservesAll();
      AU.addRequiredTransitive<FunctionWeight>();
      AU.addRequired<LoopInfoWrapperPass>();
    }

    const DataflowAnalysis<uint32_t> &getInsertCheckpointResult() const { return problem; }
    DataflowAnalysis<uint32_t> &getInsertCheckpointResult() { return problem; }

  };

  char InsertCheckpoint::ID = 0;
  RegisterPass<InsertCheckpoint> weighted_checkpoint("weighted-checkpoint",
                                       "Loop InsertCheckpointing Pass");
}

