#include "../Core/lifting.hpp"
#include "../unit_test/unit_test.hpp"

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>
#include <fstream>

int main(int argc, char** argv) {
  llvm::LLVMContext Context;

  std::unique_ptr<llvm::Module> Owner(new llvm::Module("main.c", Context));
  llvm::Module* Module = Owner.get();

  auto* f = llvm::Function::Create(
      llvm::FunctionType::get(llvm::Type::getVoidTy(Context), false),
      llvm::GlobalValue::ExternalLinkage, "root", *Module);

  llvm::BasicBlock::Create(Module->getContext(), "entry", f);
  llvm::IRBuilder<> irb(&f->front());

  auto* ret = irb.CreateRetVoid();
  irb.SetInsertPoint(ret);

  env_init(Owner);

  do_unit_test(irb);

  Module->print(llvm::outs(), nullptr);
  std::error_code e;
  llvm::raw_fd_ostream ofd("main.ll",e);
  Module->print(ofd,nullptr);

  system("opt.exe -O3 main.ll -o main_opt.bc");
  system("llc.exe main_opt.bc -x86-asm-syntax=intel -march=x86");
  system("clang.exe -c main_opt.bc -m32");

  return 0;
}