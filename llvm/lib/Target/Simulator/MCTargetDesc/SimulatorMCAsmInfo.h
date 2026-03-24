#ifndef LLVM_LIB_TARGET_SIMULATOR_MCTARGETDESC_SIMULATORMCASMINFO_H
#define LLVM_LIB_TARGET_SIMULATOR_MCTARGETDESC_SIMULATORMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class SimulatorELFMCAsmInfo : public MCAsmInfoELF {
public:
  explicit SimulatorELFMCAsmInfo(const Triple &TheTriple);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_SIMULATOR_MCTARGETDESC_SIMULATORMCASMINFO_H