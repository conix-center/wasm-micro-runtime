#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/ValueTracking.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/raw_ostream.h"

namespace llvm {

  GlobalVariable* create_int_global(Type* type, std::string name, Module* current_module) {
    StringRef global_strref(name);

    // Get a value 0, 1
    Constant* zero = ConstantInt::get(type, 0);
    
    GlobalVariable* global_cnt;
    // Create global variable reference
    if ((global_cnt = current_module->getNamedGlobal(global_strref)) == nullptr) {
      //Constant* constant = current_module->getOrInsertGlobal(global_strref, Type::getInt64Ty(current_module->getContext()));
      Constant* constant = current_module->getOrInsertGlobal(global_strref, type, [&] {
        return new GlobalVariable(*current_module, type, false, GlobalVariable::ExternalLinkage, zero, global_strref);
      });
      global_cnt = dyn_cast<GlobalVariable>(constant);
      global_cnt->setVisibility(GlobalValue::HiddenVisibility);
      //global_cnt->setInitializer(global_cnt);
    }
    // If global_cnt is nullptr, the value already exists: return it
    return global_cnt;
  }
}
