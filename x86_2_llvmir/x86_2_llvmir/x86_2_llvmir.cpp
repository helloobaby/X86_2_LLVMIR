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

  // opcode unit test
  //mov_op_test(irb);
  mov_op_test2(irb);
  // end

  Module->print(llvm::outs(), nullptr);
  std::error_code e;
  llvm::raw_fd_ostream ofd("main.ll",e);
  Module->print(ofd,nullptr);

  return 0;
}