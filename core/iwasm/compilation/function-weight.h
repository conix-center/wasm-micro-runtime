// 15-745 S16 Assignment 1: FunctionWeight.cpp
// Group: Arjun Ramesh (arjunr2) and Nishanth Subramanian (nsubram2)
////////////////////////////////////////////////////////////////////////////////

#ifndef _FUNCTION_WEIGHT_H_
#define _FUNCTION_WEIGHT_H_

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/ADT/PostOrderIterator.h"

#include "Dataflow.h"
#include <iostream>

namespace llvm {
  /* Globals used for weighted checkpoint */
  extern std::map<Function*, uint32_t> fn_straight_line_weight;
  /* Used for WAMR memory information */
  /* mem_base_addr_offset_arg set externally */
  extern uint32_t mem_base_addr_offset_arg;
  extern std::map<Function*, Value*> func_prof_context_map;

  struct LoopInfoS {
    uint32_t weight;
    bool checkpointed;
  };
  extern std::map<BasicBlock*, bool> processed_blocks;
  extern std::map<Loop*, LoopInfoS> loop_info;
  extern std::vector<std::string> instrumented_var_names_str;
  /* */


  uint32_t getInstructionWeight(Instruction* I);


  class FunctionWeight : public ModulePass {
  public:
    static char ID;
    FunctionWeight() : ModulePass(ID) { }
    ~FunctionWeight() { }


    // We don't modify the program, so we preserve all analyses
    void getAnalysisUsage(AnalysisUsage &AU) const override;


    static uint32_t transfer_fn(Value *V, uint32_t in);

    // Here, Meet is Max
    static uint32_t meet(std::vector<uint32_t> ins);

    // Print output for each function
    bool runOnModule(Module &M) override;

    void clear_instrumentation_vars();
  };

}


#endif
