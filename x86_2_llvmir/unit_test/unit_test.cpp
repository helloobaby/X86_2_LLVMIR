// unit_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "unit_test.hpp"
#include "../Core/utils.hpp"


using namespace std;


void test1() {
  auto v = keystone::util_assembly_to_bytes_32("pushf");
  for (auto &c : v) {
    printf("%x ", c);
  }
  printf("\n");
}

void test2() { keystone::util_assembly_to_bytes_32("kkkk"); }

void test3() {
  uint8_t arr[] { 0xb8, 0x01, 0x00, 0x00, 0x00 };
  ZydisDisassembledInstruction insn = zydis::ZydisDisassmbly({std::begin(arr), std::end(arr)});
  printf("%s\n", insn.text);
  uint8_t arr2[]{0x9c};
  insn = zydis::ZydisDisassmbly({std::begin(arr2), std::end(arr2)});
  printf("%s\n", insn.text);
}



int main() {
  
  test1();
  //test2();
  test3();

  return 0;
}

