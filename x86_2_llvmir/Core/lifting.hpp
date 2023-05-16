#pragma once
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"

#include "x86.h"
#include <exception>

extern std::map<ZydisRegister, llvm::GlobalVariable*> kIrGlobalRegMap; 

// all init functions
void env_init(std::unique_ptr<llvm::Module>& Module) {
  init_reg_llvmtype_map(Module);
  create_reg(Module);
}
void lift_Mov32(const ZydisDisassembledInstruction& insn, llvm::IRBuilder<>& irb);
void lift_Sub32(const ZydisDisassembledInstruction& insn, llvm::IRBuilder<>& irb);
void lift_Not32(const ZydisDisassembledInstruction& insn, llvm::IRBuilder<>& irb);

void dispatch32(const ZydisDisassembledInstruction& insn,llvm::IRBuilder<>& irb) {
  if (insn.info.mnemonic == ZYDIS_MNEMONIC_MOV) {
    printf(">> translate mov operation\n");
    lift_Mov32(insn, irb);
  } else if (insn.info.mnemonic == ZYDIS_MNEMONIC_SUB) 
  {
      printf(">> translate sub operation\n");
    lift_Sub32(insn, irb);
  } else if (insn.info.mnemonic == ZYDIS_MNEMONIC_NOT) {
    printf(">> translate not operation\n");
    lift_Not32(insn, irb);
  } 
  else {
    printf(">> dispatch failed\n");
    exit(0);
  }
}

void lift_Mov32(const ZydisDisassembledInstruction& insn,
                llvm::IRBuilder<>& irb) {
  if (insn.operands[1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE) {
    auto op_reg = insn.operands[0].reg;
    auto ir_reg = kIrGlobalRegMap.find(op_reg.value)->second;
    auto op_value = insn.operands[1].imm.value.u;
    // printf(">> %x\n", op_value);

    irb.CreateStore(irb.getInt32(op_value), ir_reg);
  } else if (insn.operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER) {
     auto op1_reg = insn.operands[0].reg;
     auto op2_reg = insn.operands[1].reg;
     auto ir_reg1 = kIrGlobalRegMap.find(op1_reg.value)->second;
     auto ir_reg2 = kIrGlobalRegMap.find(op2_reg.value)->second;
     auto op2_reg_value = irb.CreateLoad(k_r2t.find(op1_reg.value)->second, ir_reg2);
     irb.CreateStore(op2_reg_value, ir_reg1);

    
  } else {
    throw std::runtime_error("nononononono!");
  }
}

void lift_Sub32(const ZydisDisassembledInstruction& insn,
    llvm::IRBuilder<>& irb) {
  if (insn.operands[1].type == ZYDIS_OPERAND_TYPE_IMMEDIATE) {
    auto op_reg = insn.operands[0].reg;
    auto ir_reg = kIrGlobalRegMap.find(op_reg.value)->second;
    auto op_value = insn.operands[1].imm.value.u;
    // printf(">> %x\n", op_value);
    auto ir_reg_value = irb.CreateLoad(k_r2t.find(op_reg.value)->second, ir_reg);
    auto result_ptr = irb.CreateSub(ir_reg_value, irb.getInt32(op_value));
    // auto result_val = irb.CreateLoad(irb.getInt32Ty(), result_ptr);
    irb.CreateStore(result_ptr, ir_reg);
  } else if (insn.operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER) {
      auto op1_reg = insn.operands[0].reg;
     auto op2_reg = insn.operands[1].reg;
     auto ir_reg1 = kIrGlobalRegMap.find(op1_reg.value)->second;
     auto ir_reg2 = kIrGlobalRegMap.find(op2_reg.value)->second;
     auto op1_reg_value = irb.CreateLoad(k_r2t.find(op1_reg.value)->second, ir_reg1);
     auto op2_reg_value = irb.CreateLoad(k_r2t.find(op1_reg.value)->second, ir_reg2);
     auto result_ptr = irb.CreateSub(op1_reg_value, op2_reg_value);
     irb.CreateStore(result_ptr, ir_reg1);
  } else {
  throw std::runtime_error("nononononono!");
  }
}

void lift_Not32(const ZydisDisassembledInstruction& insn,
    llvm::IRBuilder<>& irb) {
    auto op_reg = insn.operands[0].reg;
    auto ir_reg = kIrGlobalRegMap.find(op_reg.value)->second;

    auto ir_reg_value = irb.CreateLoad(k_r2t.find(op_reg.value)->second,ir_reg);
    
    // llvm 'not' is samed as '!' key word in c language instead of 'not' in x86
    //auto result = irb.CreateNot(ir_reg_value);
    
    
    auto result = irb.CreateXor(ir_reg_value,llvm::LLVMGetCorrespondWidthInt(insn,irb,-1));
    irb.CreateStore(result, ir_reg);
}