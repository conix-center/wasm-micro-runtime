// 15-745 Assignment 2: available.cpp
// Group: Nishanth Subramanian (nsubram2) and Arjun Ramesh (arjunr2)
////////////////////////////////////////////////////////////////////////////////

#ifndef _WEIGHTED_CHECKPOINT_H_
#define _WEIGHTED_CHECKPOINT_H_

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
#include "aot_llvm.h"
#include "function-weight.h"
//#include "Global.h"

namespace llvm
{
  
  extern AOTCompContext* comp_ctx;
  extern std::map<Value*, uint32_t> func_ctx_idx_map;

  class WeightedCheckpoint : public LoopPass
  {

  public:

    static char ID;
    DataflowAnalysis<uint32_t> problem;

    explicit WeightedCheckpoint() : LoopPass(ID) {}

    static uint32_t transfer_fn(Value *V, uint32_t in);

    static uint32_t meet(std::vector<uint32_t> ins);

    /* Get base address to access memory array */
    Value* getMemBaseAddrPtr(Function* F);

    virtual bool doInitialization(Loop* L, LPPassManager &LPM);

    virtual bool runOnLoop(Loop* L, LPPassManager &LPM);

    virtual bool doFinalization();

    virtual void getAnalysisUsage(AnalysisUsage &AU) const;

    const DataflowAnalysis<uint32_t> &getWeightedCheckpointResult() const { return problem; }
    DataflowAnalysis<uint32_t> &getWeightedCheckpointResult() { return problem; }

  };
}

#endif
