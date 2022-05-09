// 15-745 Assignment 2: dataflow.cpp
// Group: Nishanth Subramanian (nsubram2) and Arjun Ramesh (arjunr2)
////////////////////////////////////////////////////////////////////////////////

#include "Dataflow.h"
#include "llvm/Support/raw_ostream.h"

namespace llvm {


  template<typename DomainSet>
  void DataflowAnalysis<DomainSet>::run_iterations(Function &F, Direction _direction, 
        Granularity _granularity) {

    direction = _direction;
    granularity = _granularity;
    BasicBlock *entryBlock = &F.getEntryBlock();
    std::queue<BasicBlock *> traverse_queue;

    // Forward direction
    if (direction == FORWARDS)
    {
      // Initialize boundary conditions, top, traversed
      // Add first BB to queue
      BB_state[entryBlock].in = boundary;
      traverse_queue.push(entryBlock);
      for (BasicBlock &BB : F)
      {
        BB_state[&BB].out = top;
        BB_state[&BB].traversed = false;
      }

      // Traverse basic blocks using BFS
      while (!traverse_queue.empty())
      {
        BasicBlock *BB = traverse_queue.front();
        traverse_queue.pop();
        BB_state[BB].traversed = true;
        BB_state[BB].name = BB->getName();

        // Get predecessors
        std::vector<DomainSet> preds_out;
        int count = 0;
        // Entry block, include input from entry
        if (BB == entryBlock)
        {
          preds_out.push_back(BB_state[entryBlock].in);
          count++;
        }
        for (BasicBlock *pred : predecessors(BB))
        {
          DomainSet pred_out = BB_state[pred].out;
          preds_out.push_back(pred_out);
          count++;
        }

        // IN[BB] = MEET(BB.predecessors)
        BB_state[BB].in = meet(preds_out);

        // Propagate TransferFn through BB
        // Generate OUT[BB] = TransFn(BB, IN[BB])
        DomainSet tempSet = BB_state[BB].in;
        DomainSet prev_out = BB_state[BB].out;
        if (granularity == INSTRUCTIONS) {
          for (Instruction &I : *BB)
          {
            BB_state[BB].insn[&I].in = tempSet;
            tempSet = transfer_fn(&I, tempSet);
            BB_state[BB].insn[&I].out = tempSet;
          }
          BB_state[BB].out = tempSet;
        }
        else {
          BB_state[BB].out = transfer_fn(BB, tempSet);
        }

        if (BB_state[BB].out != prev_out)
        {
          // If OUT[BB] changed, insert successors to queue
          for (BasicBlock *succ : successors(BB))
            traverse_queue.push(succ);
        }
        else
        {
          // If OUT[BB] stayed the same, add untraversed successors to queue
          for (BasicBlock *succ : successors(BB))
            if (BB_state[succ].traversed == false)
              traverse_queue.push(succ);
        }
      }
    }

    // Reverse direction
    else
    {
      std::vector<BasicBlock *> exit_blocks;
      for (BasicBlock &BB : F)
      {
        for (Instruction &I : BB)
        {
          // Detect Exit blocks, push them all into queue
          if (ReturnInst *ret_inst = dyn_cast<ReturnInst>(&I))
          {
            // Initialize boundary conditions
            BB_state[&BB].in = boundary;
            traverse_queue.push(&BB);
            exit_blocks.push_back(&BB);
          }
        }
        // Initialize top, traversed
        BB_state[&BB].out = top;
        BB_state[&BB].traversed = false;
      }

      // Traverse basic blocks using BFS
      while (!traverse_queue.empty())
      {
        BasicBlock *BB = traverse_queue.front();
        traverse_queue.pop();
        BB_state[BB].traversed = true;

        // Get successors
        std::vector<DomainSet> succs_out;
        int count = 0;
        // Exit block, include output from exit
        for (auto &exit_block : exit_blocks)
        {
          if (exit_block == BB)
          {
            succs_out.push_back(BB_state[BB].in);
            count++;
          }
        }
        for (BasicBlock *succ : successors(BB))
        {
          DomainSet succ_out = BB_state[succ].out;
          succs_out.push_back(succ_out);
          count++;
        }

        // Compute Meet operation on successors
        BB_state[BB].in = meet(succs_out);

        // Generate TransFn
        DomainSet tempSet = BB_state[BB].in;
        DomainSet prev_out = BB_state[BB].out;
        if (granularity == INSTRUCTIONS) {
          // Traverse basic block in reverse
          for (BasicBlock::reverse_iterator i = BB->rbegin(); i != BB->rend(); ++i)
          {
            Instruction *I = &*i;
            BB_state[BB].insn[I].in = tempSet;
            tempSet = transfer_fn(I, tempSet);
            BB_state[BB].insn[I].out = tempSet;
          }
          BB_state[BB].out = tempSet;
        }
        else {
          BB_state[BB].out = transfer_fn(BB, tempSet);
        }

        if (BB_state[BB].out != prev_out)
        {
          // If OUT[BB] changed, insert predecessors to queue
          for (BasicBlock *pred : predecessors(BB))
            traverse_queue.push(pred);
        }
        else
        {
          // If OUT[BB] stayed the same, add untraversed predecessors to queue
          for (BasicBlock *pred : predecessors(BB))
            if (BB_state[pred].traversed == false)
              traverse_queue.push(pred);
        }
      }
    }
  }
  template void DataflowAnalysis<BitVector>::run_iterations(Function &F, Direction  _direction, Granularity _granularity);
  template void DataflowAnalysis<uint32_t>::run_iterations(Function &F, Direction  _direction, Granularity _granularity);






  template<typename DomainSet>
  void DataflowAnalysis<DomainSet>::run_iterations_loop(Loop* L, LoopInfo* LICP, Direction _direction, 
        Granularity _granularity) {

    direction = _direction;
    granularity = _granularity;
    BasicBlock *entryBlock = L->getHeader();
    std::queue<BasicBlock *> traverse_queue;

    // Forward direction
    // Initialize boundary conditions, top, traversed
    // Add first BB to queue
    BB_state[entryBlock].in = boundary;
    traverse_queue.push(entryBlock);
    for (BasicBlock* BB : L->blocks())
    {
      BB_state[BB].out = top;
      BB_state[BB].traversed = false;
    }

    // Traverse basic blocks using BFS
    while (!traverse_queue.empty())
    {
      BasicBlock *BB = traverse_queue.front();
      traverse_queue.pop();
      BB_state[BB].traversed = true;
      BB_state[BB].name = BB->getName();

      // Get predecessors
      std::vector<DomainSet> preds_out;
      int count = 0;
      // Entry block, include input from entry
      if (BB == entryBlock)
      {
        preds_out.push_back(BB_state[entryBlock].in);
        count++;
      }
      for (BasicBlock *pred : predecessors(BB))
      {
        DomainSet pred_out = BB_state[pred].out;
        preds_out.push_back(pred_out);
        count++;
      }

      // IN[BB] = MEET(BB.predecessors)
      BB_state[BB].in = meet(preds_out);

      // Propagate TransferFn through BB
      // Generate OUT[BB] = TransFn(BB, IN[BB])
      DomainSet tempSet = BB_state[BB].in;
      DomainSet prev_out = BB_state[BB].out;
      if (granularity == INSTRUCTIONS) {
        for (Instruction &I : *BB)
        {
          BB_state[BB].insn[&I].in = tempSet;
          tempSet = transfer_fn(&I, tempSet);
          BB_state[BB].insn[&I].out = tempSet;
        }
        BB_state[BB].out = tempSet;
      }
      else {
        BB_state[BB].out = transfer_fn(BB, tempSet);
      }

      // Add untraversed successors to queue that are in the loop
      for (BasicBlock *succ : successors(BB)) {
        Loop* bbl = LICP->getLoopFor(succ);
        // Blocks in inner or outside loop: Add their successors as long as untraversed
        if ((bbl != L) && BB_state[succ].traversed == false && L->contains(succ)) {
          traverse_queue.push(succ);
        }
        // Blocks in current loop: Add their successors only if all predecessors are traversed
        else if (bbl == L) {
          bool ready = true;
          for (BasicBlock * pred : predecessors(succ)) {
            ready &= BB_state[pred].traversed;
          }
          if (ready) {
            traverse_queue.push(succ);
          }
        }
      }
    }
  }
  template void DataflowAnalysis<uint32_t>::run_iterations_loop(Loop* L, LoopInfo* LICP, Direction  _direction, Granularity _granularity);
  template void DataflowAnalysis<BitVector>::run_iterations_loop(Loop* L, LoopInfo* LICP, Direction  _direction, Granularity _granularity);




  /*
  template<typename DomainSet>
  void DataflowAnalysis<DomainSet>::print_expression_state(Function &F, std::vector<Expression> univ_set) {
    outs() << "\nIR:\n\n";
    for (auto &BB : F)
    {
      outs() << "<----------------------------- ";
      DomainSet vec = BB_state[&BB].in;
      std::vector<Expression> inst_set;
      for (auto idx = vec.set_bits_begin(); idx != vec.set_bits_end(); ++idx)
      {
        inst_set.push_back(univ_set[*idx]);
      }
      printSet(&inst_set);

      Instruction *I;
      for (auto &Inst : BB)
      {
        outs() << Inst << "\n";
        I = &Inst;
        outs() << "<----------------------------- ";
        DomainSet vec = BB_state[&BB].insn[I].out;
        std::vector<Expression> inst_set;
        for (auto idx = vec.set_bits_begin(); idx != vec.set_bits_end(); ++idx)
        {
          inst_set.push_back(univ_set[*idx]);
        }
        printSet(&inst_set);
      }
    }
  }
  template void DataflowAnalysis<BitVector>::print_expression_state(Function &F, std::vector<Expression> univ_set);
  */


  /*
  template<typename DomainSet>
  void DataflowAnalysis<DomainSet>::print_variable_state(Function &F, std::vector<Value *> univ_set) {
    outs() << "\nIR:\n\n";
    for (auto &BB : F)
    {
      Instruction *I;
      // Backwards prints
      if (direction == BACKWARDS) {
        // printSet(&inst_set);
        for (auto &Inst : BB)
        {
          I = &Inst;

          outs() << "<----------------------------- { ";

          DomainSet vec = BB_state[&BB].insn[I].out;
          for (auto idx = vec.set_bits_begin(); idx != vec.set_bits_end(); ++idx)
          {
            outs() << getShortValueName(univ_set[*idx]) << " , ";
          }
          outs() << " }\n";
          outs() << Inst << "\n";

        }
        outs() << "<----------------------------- { ";
        DomainSet vec = BB_state[&BB].in;
        std::vector<Value *> inst_set;
        for (auto idx = vec.set_bits_begin(); idx != vec.set_bits_end(); ++idx)
        {
          outs() << getShortValueName(univ_set[*idx]) << " , ";
        }
        outs() << " }\n";
      }

      // Forward prints
      else {
        outs() << "<----------------------------- { ";
        DomainSet vec = BB_state[&BB].in;
        for (auto idx = vec.set_bits_begin(); idx != vec.set_bits_end(); ++idx)
        {
          outs() << *univ_set[*idx] << " , ";
        }
        outs() << " }\n\n";

        for (auto &Inst : BB)
        {
          outs() << Inst << "\n";
          I = &Inst;
          outs() << "<----------------------------- { ";
          DomainSet vec = BB_state[&BB].insn[I].out;
          for (auto idx = vec.set_bits_begin(); idx != vec.set_bits_end(); ++idx)
          {
            outs() << *univ_set[*idx] << " , ";
          }
          outs() << " }\n\n";
        }
      }
    }
  }
  template void DataflowAnalysis<BitVector>::print_variable_state(Function &F, std::vector<Value *> univ_set);
  */

  /*
  template<typename DomainSet>
  void DataflowAnalysis<DomainSet>::print_variable_state_loop(Loop* L, std::vector<Value *> univ_set) {
    outs() << "\nIR:\n\n";
    for (auto &BB : L->blocks())
    {
      Instruction *I;
      // Backwards prints
      if (direction == BACKWARDS) {
        // printSet(&inst_set);
        for (auto &Inst : *BB)
        {
          I = &Inst;

          outs() << "<----------------------------- { ";

          DomainSet vec = BB_state[BB].insn[I].out;
          for (auto idx = vec.set_bits_begin(); idx != vec.set_bits_end(); ++idx)
          {
            outs() << getShortValueName(univ_set[*idx]) << " , ";
          }
          outs() << " }\n";
          outs() << Inst << "\n";

        }
        outs() << "<----------------------------- { ";
        DomainSet vec = BB_state[BB].in;
        std::vector<Value *> inst_set;
        for (auto idx = vec.set_bits_begin(); idx != vec.set_bits_end(); ++idx)
        {
          outs() << getShortValueName(univ_set[*idx]) << " , ";
        }
        outs() << " }\n";
      }

      // Forward prints
      else {
        outs() << "<----------------------------- { ";
        DomainSet vec = BB_state[BB].in;
        for (auto idx = vec.set_bits_begin(); idx != vec.set_bits_end(); ++idx)
        {
          outs() << *univ_set[*idx] << " , ";
        }
        outs() << " }\n\n";

        for (auto &Inst : *BB)
        {
          outs() << Inst << "\n";
          I = &Inst;
          outs() << "<----------------------------- { ";
          DomainSet vec = BB_state[BB].insn[I].out;
          for (auto idx = vec.set_bits_begin(); idx != vec.set_bits_end(); ++idx)
          {
            outs() << *univ_set[*idx] << " , ";
          }
          outs() << " }\n\n";
        }
      }
    }
  }
  template void DataflowAnalysis<BitVector>::print_variable_state_loop(Loop* L, std::vector<Value *> univ_set);
  */




  template<typename DomainSet>
  DomainSet DataflowAnalysis<DomainSet>::get_outs(Value *V, Granularity granularity) {
    DomainSet out;
    if (granularity == BASIC_BLOCKS) {
      BasicBlock* BB = dyn_cast<BasicBlock>(V);
      out = BB_state[BB].out;
      //out = ((direction == FORWARDS) ? BB_state[BB].out : BB_state[BB].out);
    } else {
      Instruction* I = dyn_cast<Instruction>(V);
      BasicBlock* BB = I->getParent();
      out = BB_state[BB].insn[I].out;
      //out = ((direction == FORWARDS) ? BB_state[BB].insn[I].out : BB_state[BB].insn[I].out);
    }
    return out;
  }
  template BitVector DataflowAnalysis<BitVector>::get_outs(Value *V, Granularity granularity);
  template uint32_t DataflowAnalysis<uint32_t>::get_outs(Value *V, Granularity granularity);

}
