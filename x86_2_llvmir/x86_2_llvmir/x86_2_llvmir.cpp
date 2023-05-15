#include "../Core/lifting.hpp"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>
#include <fstream>

using namespace llvm;

int main(int argc, char** argv) {
  LLVMContext Context;

  std::unique_ptr<Module> Owner(new Module("main.c", Context));
  Module* Module = Owner.get();

  auto* f = llvm::Function::Create(
      llvm::FunctionType::get(llvm::Type::getVoidTy(Context), false),
      llvm::GlobalValue::ExternalLinkage, "root", *Module);

  llvm::BasicBlock::Create(Module->getContext(), "entry", f);
  llvm::IRBuilder<> irb(&f->front());

  auto* ret = irb.CreateRetVoid();
  irb.SetInsertPoint(ret);

  env_init(Owner);
  init_reg_llvmtype_map(Owner);
  create_reg(Owner);

  auto bytes = keystone::util_assembly_to_bytes_32("mov     eax, 0FFFFFFFFh");
  dispatch32(zydis::ZydisDisassmbly(bytes),irb);
  bytes = keystone::util_assembly_to_bytes_32("sub     eax, 0F3h");
  dispatch32(zydis::ZydisDisassmbly(bytes),irb);
  bytes = keystone::util_assembly_to_bytes_32("not     eax");
  //dispatch32(zydis::ZydisDisassmbly(bytes),irb);

  Module->print(outs(), nullptr);
  std::error_code e;
  llvm::raw_fd_ostream ofd("main.ll",e);
  Module->print(ofd,nullptr);

  system("opt.exe -O3 main.ll -o main_opt.bc");
  system("llc.exe main_opt.bc -x86-asm-syntax=intel -march=x86");
  system("clang.exe -c main_opt.bc -m32");


  return 0;
}