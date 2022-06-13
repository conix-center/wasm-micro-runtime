// 15-745 Assignment 2: available.cpp
// Group: Nishanth Subramanian (nsubram2) and Arjun Ramesh (arjunr2)
////////////////////////////////////////////////////////////////////////////////

#include "weighted-checkpoint.h"

using namespace llvm;
using namespace std;

namespace llvm {
  static cl::opt<uint32_t> Threshold("threshold", cl::desc("Threshold for checkpointing"), cl::init(30));

  std::vector<Value *> universal_blocks;
  LoopInfo* LICP;
  Loop* current_loop;
  unsigned current_loop_depth;
  Module* current_module;

  AOTCompContext* comp_ctx;
  std::map<Value*, uint32_t> func_ctx_idx_map;  

  char WeightedCheckpoint::ID = 0;
  RegisterPass<WeightedCheckpoint> weighted_checkpoint("weighted-checkpoint",
                                       "Loop WeightedCheckpointing Pass");

}


uint32_t WeightedCheckpoint::transfer_fn(Value *V, uint32_t in) {
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
uint32_t WeightedCheckpoint::meet(std::vector<uint32_t> ins)
{
  uint32_t max = *max_element(ins.begin(), ins.end());
  return max;
}



/* Get base address to access memory array */
Value* WeightedCheckpoint::getMemBaseAddrPtr(Function* F) {
  if (func_prof_context_map.find(F) != func_prof_context_map.end()) {
    return func_prof_context_map[F];
  }
  else {
    Instruction* aot_inst_addr = F->getEntryBlock().getFirstNonPHI();
    Instruction* insert_pt = aot_inst_addr->getNextNonDebugInstruction();
    
    // Types
    Type* int8_type = Type::getInt8Ty(current_module->getContext());
    Type* int8_ptr_type = Type::getInt8PtrTy(current_module->getContext());
    Type* int8_2ptr_type = PointerType::getUnqual(int8_ptr_type);
    Type* int64_type = Type::getInt64Ty(current_module->getContext());
    Type* int64_ptr_type = Type::getInt64PtrTy(current_module->getContext());

    // Insert profiling variables after
    IRBuilder<> Builder(insert_pt);

    //Value* aot_inst = 
    //  Builder.CreateAlignedLoad(int8_ptr_type, aot_inst_addr, MaybeAlign(8), "prof_aot_inst");

    Value* aot_inst1 = 
      Builder.CreateBitCast(aot_inst_addr, int64_ptr_type, "p0");
    Value* aot_inst2 =
      Builder.CreateAlignedLoad(int64_type, aot_inst1, MaybeAlign(8), "p1");
    Value* aot_inst = 
      Builder.CreateIntToPtr(aot_inst2, int8_ptr_type, "prof_aot_inst");

    Value* mem_base_addr_offset = 
      Builder.CreateConstInBoundsGEP1_64(int8_type, aot_inst, mem_base_addr_offset_arg, "prof_mem_base_addr_offset");
    Value* mem_base_addr_ptr = 
      Builder.CreateBitCast(mem_base_addr_offset, int8_2ptr_type, "prof_mem_base_addr_ptr");
    Value* mem_base_addr =
      Builder.CreateAlignedLoad(int8_ptr_type, mem_base_addr_ptr, MaybeAlign(8), "prof_mem_base_addr");

    func_prof_context_map[F] = mem_base_addr;
    return mem_base_addr;
  }
}


bool WeightedCheckpoint::doInitialization(Loop* L, LPPassManager &LPM) {
  string fn_name = L->getHeader()->getParent()->getName().str();
  return false;
}


bool WeightedCheckpoint::runOnLoop(Loop* L, LPPassManager &LPM) {
  // Initialization
  Function* F = L->getHeader()->getParent();
  
  current_loop = L;
  current_loop_depth = L->getLoopDepth();
  current_module = L->getHeader()->getModule();
  LICP = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();

  uint32_t top = 0;
  uint32_t entry = 0;
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
    

  uint32_t fn_idx = func_ctx_idx_map[F];
  string prefix = "rtinstloop";
  string fn_name = F->getName().str();
  string loop_name = L->getName().str();
  string var_name = prefix + "_" + fn_name + "_" + loop_name;

  // Checkpoint above threshold
  uint32_t THRESHOLD = Threshold;

  if (loop_weight > THRESHOLD || true) {
    loop_info[L].checkpointed = true;
    instrumented_var_names_str.push_back(var_name);
    outs() << "[#" << func_ctx_idx_map[F] << "] "  << loop_name 
              << " | W/T: " << loop_weight << "/" << THRESHOLD
              << " ==> Inserting Checkpoint: \'" << var_name << "\'\n";

    // Instrument
    Type* int32_type = Type::getInt32Ty(current_module->getContext());
    Type* int32_ptr_type = Type::getInt32PtrTy(current_module->getContext());
    Type* int64_type = Type::getInt64Ty(current_module->getContext());
    Type* int8_ptr_type = Type::getInt8PtrTy(current_module->getContext());
    Type* int8_type = Type::getInt8Ty(current_module->getContext());

    Constant* one = ConstantInt::get(int64_type, 1);
    uint64_t inst_base = (comp_ctx->comp_data->memories[0].mem_init_page_count) *
                          comp_ctx->comp_data->memories[0].num_bytes_per_page;

    // Builder
    Instruction* Inst = L->getHeader()->getFirstNonPHI();
    IRBuilder<> Builder(Inst);

    // 1. Get memory base address
    Value* mem_base_addr = getMemBaseAddrPtr(F);

    // 2. Get instrument address
    Value* inst_addr = Builder.CreateConstInBoundsGEP1_64(int8_type, 
                          mem_base_addr, inst_base + 4*(instrumented_var_names_str.size() - 1), "prof_addr");
    Value* inst_addr_cast = Builder.CreateBitCast(inst_addr, int32_ptr_type, "prof_addr_cast");
    LoadInst* li = Builder.CreateLoad(int32_type, inst_addr_cast, true, "lp_ld");
    Value* inc = Builder.CreateAdd(li, one, "lp_add");
    StoreInst* si = Builder.CreateStore(inc, inst_addr_cast);
  }
  // Modifies the incoming Function.
  return true;
}



bool WeightedCheckpoint::doFinalization() {
  return false;
}


void WeightedCheckpoint::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
  AU.addRequiredTransitive<FunctionWeight>();
  AU.addRequired<LoopInfoWrapperPass>();
}

