#include "llvm/IR/IRBuilder.h"
#include "../Core/lifting.hpp"

void mov_op_test(llvm::IRBuilder<>& irb) {
  auto bytes = keystone::util_assembly_to_bytes_32("mov     eax, 1");
  dispatch32(zydis::ZydisDisassmbly(bytes), irb);
}

void mov_op_test2(llvm::IRBuilder<>& irb) {
  auto bytes = keystone::util_assembly_to_bytes_32("mov     eax, ebx");
  dispatch32(zydis::ZydisDisassmbly(bytes), irb);
}
