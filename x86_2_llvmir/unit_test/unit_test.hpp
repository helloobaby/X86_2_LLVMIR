#include "llvm/IR/IRBuilder.h"
#include "../Core/lifting.hpp"

void mov_op_test(llvm::IRBuilder<>& irb) {
  auto bytes = keystone::util_assembly_to_bytes_32("mov     eax, 10"); //eax = 10
  dispatch32(zydis::ZydisDisassmbly(bytes), irb);
  bytes = keystone::util_assembly_to_bytes_32("mov     ebx, 20"); //ebx=20
  dispatch32(zydis::ZydisDisassmbly(bytes), irb);
}

void mov_op_test2(llvm::IRBuilder<>& irb) {
  auto bytes = keystone::util_assembly_to_bytes_32("mov     eax, ebx");//eax=20
  dispatch32(zydis::ZydisDisassmbly(bytes), irb);
}
void sub_op_test1(llvm::IRBuilder<>& irb) {
	 auto bytes = keystone::util_assembly_to_bytes_32("sub     eax, 1");//eax=19
  dispatch32(zydis::ZydisDisassmbly(bytes), irb);
}

void sub_op_test2(llvm::IRBuilder<>& irb) {
	 auto bytes = keystone::util_assembly_to_bytes_32("sub     eax, ebx");//eax=-1
  dispatch32(zydis::ZydisDisassmbly(bytes), irb);
}

void mov_op_test3(llvm::IRBuilder<>& irb) {
	//auto bytes = keystone::util_assembly_to_bytes_32("mov     ax, bx"); //eax = 0xffff0014
  //dispatch32(zydis::ZydisDisassmbly(bytes), irb);
}

void not_op_test1(llvm::IRBuilder<>& irb) {
	auto bytes = keystone::util_assembly_to_bytes_32("not eax");// eax = 0xffeb(65515)
  dispatch32(zydis::ZydisDisassmbly(bytes), irb);
}

// put all unit tests
void do_unit_test(llvm::IRBuilder<>& irb) {
  mov_op_test(irb); 
  mov_op_test2(irb); 
  sub_op_test1(irb);
  sub_op_test2(irb);
  mov_op_test3(irb);
  not_op_test1(irb);
}