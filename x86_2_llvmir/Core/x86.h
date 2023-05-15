#pragma once
#include <map>

#include "Zydis.h"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"


std::map<uint32_t, llvm::Type*> k_r2t;
std::map<ZydisRegister, llvm::GlobalVariable*> kIrGlobalRegMap; 

void init_reg_llvmtype_map(std::unique_ptr<llvm::Module>& Module) {
	auto* i1 = llvm::IntegerType::getInt1Ty(Module->getContext());
	auto* i2 = llvm::IntegerType::getIntNTy(Module->getContext(), 2);
	auto* i3 = llvm::IntegerType::getIntNTy(Module->getContext(), 3);
	auto* i8 = llvm::IntegerType::getInt8Ty(Module->getContext());
	auto* i16 = llvm::IntegerType::getInt16Ty(Module->getContext());
	auto* i32 = llvm::IntegerType::getInt32Ty(Module->getContext());
	auto* i64 = llvm::IntegerType::getInt64Ty(Module->getContext());
	auto* i128 = llvm::IntegerType::getInt128Ty(Module->getContext());
	auto* i256 = llvm::IntegerType::getIntNTy(Module->getContext(), 256);
	auto* i512 = llvm::IntegerType::getIntNTy(Module->getContext(), 512);
	auto* fp64 = llvm::IntegerType::getDoubleTy(Module->getContext());
	auto* fp80 = llvm::IntegerType::getX86_FP80Ty(Module->getContext());
	std::map<uint32_t, llvm::Type*> r2t =
	{
			{ZYDIS_REGISTER_AH, i8},
			{ZYDIS_REGISTER_AL, i8},
			{ZYDIS_REGISTER_CH, i8},
			{ZYDIS_REGISTER_CL, i8},
			{ZYDIS_REGISTER_DH, i8},
			{ZYDIS_REGISTER_DL, i8},
			{ZYDIS_REGISTER_BH, i8},
			{ZYDIS_REGISTER_BL, i8},
			{ZYDIS_REGISTER_SPL, i8},
			{ZYDIS_REGISTER_BPL, i8},
			{ZYDIS_REGISTER_DIL, i8},
			{ZYDIS_REGISTER_SIL, i8},
			{ZYDIS_REGISTER_R8B, i8},
			{ZYDIS_REGISTER_R9B, i8},
			{ZYDIS_REGISTER_R10B, i8},
			{ZYDIS_REGISTER_R11B, i8},
			{ZYDIS_REGISTER_R12B, i8},
			{ZYDIS_REGISTER_R13B, i8},
			{ZYDIS_REGISTER_R14B, i8},
			{ZYDIS_REGISTER_R15B, i8},

			{ZYDIS_REGISTER_AX, i16},
			{ZYDIS_REGISTER_CX, i16},
			{ZYDIS_REGISTER_DX, i16},
			{ZYDIS_REGISTER_BP, i16},
			{ZYDIS_REGISTER_BX, i16},
			{ZYDIS_REGISTER_DI, i16},
			{ZYDIS_REGISTER_SP, i16},
			{ZYDIS_REGISTER_SI, i16},
			{ZYDIS_REGISTER_SS, i16},
			{ZYDIS_REGISTER_CS, i16},
			{ZYDIS_REGISTER_DS, i16},
			{ZYDIS_REGISTER_ES, i16},
			{ZYDIS_REGISTER_FS, i16},
			{ZYDIS_REGISTER_GS, i16},
			{ZYDIS_REGISTER_R8W, i16},
			{ZYDIS_REGISTER_R9W, i16},
			{ZYDIS_REGISTER_R10W, i16},
			{ZYDIS_REGISTER_R11W, i16},
			{ZYDIS_REGISTER_R12W, i16},
			{ZYDIS_REGISTER_R13W, i16},
			{ZYDIS_REGISTER_R14W, i16},
			{ZYDIS_REGISTER_R15W, i16},
			{ZYDIS_REGISTER_IP, i16},

			{ZYDIS_REGISTER_EAX, i32},
			{ZYDIS_REGISTER_EBP, i32},
			{ZYDIS_REGISTER_EBX, i32},
			{ZYDIS_REGISTER_ECX, i32},
			{ZYDIS_REGISTER_EDI, i32},
			{ZYDIS_REGISTER_EDX, i32},
			{ZYDIS_REGISTER_ESI, i32},
			{ZYDIS_REGISTER_ESP, i32},
			{ZYDIS_REGISTER_R8D, i32},
			{ZYDIS_REGISTER_R9D, i32},
			{ZYDIS_REGISTER_R10D, i32},
			{ZYDIS_REGISTER_R11D, i32},
			{ZYDIS_REGISTER_R12D, i32},
			{ZYDIS_REGISTER_R13D, i32},
			{ZYDIS_REGISTER_R14D, i32},
			{ZYDIS_REGISTER_R15D, i32},
			{ZYDIS_REGISTER_EIP, i32},

			{ZYDIS_REGISTER_RAX, i64},
			{ZYDIS_REGISTER_RBP, i64},
			{ZYDIS_REGISTER_RBX, i64},
			{ZYDIS_REGISTER_RCX, i64},
			{ZYDIS_REGISTER_RDI, i64},
			{ZYDIS_REGISTER_RDX, i64},
			{ZYDIS_REGISTER_RIP, i64},
			{ZYDIS_REGISTER_RSI, i64},
			{ZYDIS_REGISTER_RSP, i64},
			{ZYDIS_REGISTER_R8, i64},
			{ZYDIS_REGISTER_R9, i64},
			{ZYDIS_REGISTER_R10, i64},
			{ZYDIS_REGISTER_R11, i64},
			{ZYDIS_REGISTER_R12, i64},
			{ZYDIS_REGISTER_R13, i64},
			{ZYDIS_REGISTER_R14, i64},
			{ZYDIS_REGISTER_R15, i64},	
	};
        k_r2t = std::move(r2t);
}
llvm::GlobalVariable* create_reg(std::unique_ptr<llvm::Module>& Module) {
  Module->getOrInsertGlobal("eax", k_r2t.find(ZYDIS_REGISTER_EAX)->second);
  // default link type is ExternalLinkage
  // Module->getNamedGlobal("eax")->setLinkage(llvm::GlobalValue::ExternalLinkage);

  Module->getOrInsertGlobal("ebx", k_r2t.find(ZYDIS_REGISTER_EBX)->second);
  Module->getOrInsertGlobal("ecx", k_r2t.find(ZYDIS_REGISTER_ECX)->second);
  Module->getOrInsertGlobal("edx", k_r2t.find(ZYDIS_REGISTER_EDX)->second);
  Module->getOrInsertGlobal("esi", k_r2t.find(ZYDIS_REGISTER_ESI)->second);
  Module->getOrInsertGlobal("edi", k_r2t.find(ZYDIS_REGISTER_EDI)->second);

  kIrGlobalRegMap.insert({ZYDIS_REGISTER_EAX, Module->getNamedGlobal("eax")});
  kIrGlobalRegMap.insert({ZYDIS_REGISTER_EBX, Module->getNamedGlobal("ebx")});
  kIrGlobalRegMap.insert({ZYDIS_REGISTER_ECX, Module->getNamedGlobal("ecx")});
  kIrGlobalRegMap.insert({ZYDIS_REGISTER_EDX, Module->getNamedGlobal("edx")});
  kIrGlobalRegMap.insert({ZYDIS_REGISTER_ESI, Module->getNamedGlobal("esi")});
  kIrGlobalRegMap.insert({ZYDIS_REGISTER_EDI, Module->getNamedGlobal("edi")});

  return nullptr;
}