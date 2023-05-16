#pragma once 
#include <keystone/keystone.h>
#include <vector>
#include <iterator>
#include "Zydis.h"

extern ZydisRegisterWidth ZydisRegisterGetWidth(ZydisMachineMode mode,
                                                ZydisRegister reg);

namespace keystone {
ks_engine *ks = nullptr;
// https://github.com/keystone-engine/keystone/blob/master/samples/sample.c
int init_ks(ks_arch arch, int mode, int syntax) {
  ks_err err;

  err = ks_open(arch, mode, &ks);
  if (err != KS_ERR_OK) {
    return -1;
  }

  if (syntax) ks_option(ks, KS_OPT_SYNTAX, syntax);

  return KS_ERR_OK;
}

std::vector<uint8_t> util_assembly_to_bytes_32(const std::string &insn_str) {
  if (!ks) {
    int r = init_ks(KS_ARCH_X86, KS_MODE_32, 1);
    if (r != KS_ERR_OK) {  // error
      printf(">> keystone init failed\n");
      exit(0);
    }
  }

  ks_err err;
  size_t count;
  unsigned char *encode;
  size_t size;
  int r = ks_asm(ks, insn_str.c_str(), 0, &encode, &size, &count);
  if (r != KS_ERR_OK) {
    printf(">> ks_asm failed\n");
    exit(0);
  }
  uint8_t *uencode = encode;
  return std::vector<uint8_t>(uencode,uencode+size);
}

std::vector<uint8_t> util_assembly_to_bytes_64() { return {}; }
}  // namespace keystone


namespace zydis {
ZydisDisassembledInstruction ZydisDisassmbly(const std::vector<uint8_t> &bytes) {
  ZydisDisassembledInstruction insn;
  ZydisDisassembleIntel(ZYDIS_MACHINE_MODE_LONG_COMPAT_32, (ZyanU64)0,
                        bytes.data(), bytes.size(), &insn);
  return insn;
}
}  // namespace zydis

namespace llvm {

auto LLVMGetCorrespondWidthInt(const ZydisDisassembledInstruction &insn,
                               llvm::IRBuilder<> &irb, uint64_t C) {
  auto width = ZydisRegisterGetWidth(ZYDIS_MACHINE_MODE_LONG_COMPAT_32,
                                     insn.operands[0].reg.value);
  if (width == 8) {
    return irb.getInt8(C);
  } else if (width == 16) {
    return irb.getInt16(C);
  } else if (width == 32) {
    return irb.getInt32(C);
  } else {
    throw std::runtime_error("nonononoono!\n");
  }
}
}  // namespace llvm