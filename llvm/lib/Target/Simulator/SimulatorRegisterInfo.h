#ifndef LLVM_LIB_TARGET_SIMULATOR_SIMULATORREGISTERINFO_H
#define LLVM_LIB_TARGET_SIMULATOR_SIMULATORREGISTERINFO_H

#define GET_REGINFO_HEADER
#include "SimulatorGenRegisterInfo.inc"

namespace llvm {

struct SimulatorRegisterInfo : public SimulatorGenRegisterInfo {
public:
  SimulatorRegisterInfo();
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_SIMULATOR_SIMULATORREGISTERINFO_H