// 15-745 Assignment 2: dataflow.h
// Group:
////////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef __CLASSICAL_DATAFLOW_H__
#define __CLASSICAL_DATAFLOW_H__

#include <stdio.h>
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <set>

#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/IR/ValueMap.h"
#include "llvm/IR/CFG.h"

namespace llvm
{
  typedef enum {
    BASIC_BLOCKS,
    INSTRUCTIONS
  } Granularity;

  typedef enum {
    FORWARDS,
    BACKWARDS
  } Direction;

  // Domainset here is a datatype (template)
  template <typename DomainSet>
  class DataflowAnalysis
  {

    // Transfer Function takes an instruction and a domainset as input
    typedef DomainSet (*TransferFn)(Value *, DomainSet);

    // Meet operation is done on a list of Domainsets
    typedef DomainSet (*MeetFn)(std::vector<DomainSet>);

  private:
    // BasicBlock properties
    struct Interface {
      DomainSet in;
      DomainSet out;
    };
    class BB_Interface
    {
    public:
      DomainSet in;
      DomainSet out;
      std::map<Instruction *, Interface> insn;
      StringRef name;
      bool traversed;
    };

    // Dataflow requirements
    Direction direction;
    bool granularity;
    
    DomainSet boundary;
    std::map<BasicBlock *, BB_Interface> BB_state;
    TransferFn transfer_fn;
    MeetFn meet;
    DomainSet top;

  public:

    DataflowAnalysis() { };

    DataflowAnalysis(TransferFn _transfer_fn, MeetFn _meet,
                     DomainSet _boundary, DomainSet _top) : transfer_fn(_transfer_fn), meet(_meet),
                                                            boundary(_boundary), top(_top) {}


    void set(TransferFn _transfer_fn, MeetFn _meet, DomainSet _boundary, DomainSet _top) {
      transfer_fn = _transfer_fn;
      meet = _meet;
      boundary = _boundary;
      top = _top;
    }

    // This function iterates over a function in a particular direction and populates the IN/OUT DomainSets
    void run_iterations(Function &F, Direction _direction, Granularity granularity);

    // This function iterates over a function in a particular direction and populates the IN/OUT DomainSets
    void run_iterations_loop(Loop* L, LoopInfo* LICP, Direction _direction, Granularity granularity);

    // Given a function, print final state of expressions at every program point
    //void print_expression_state(Function &F, std::vector<Expression> univ_set);

    // Given a function, print final state of values at every program point
    void print_variable_state(Function &F, std::vector<Value *> univ_set);

    // Given a function, print final state of values at every program point
    void print_variable_state_loop(Loop* L, std::vector<Value *> univ_set);

    // Get the output set for a given value based on its granularity, INSTRUCTIONS or BASIC BLOCKS
    DomainSet get_outs (Value* V, Granularity granularity);

  };
}

#endif
