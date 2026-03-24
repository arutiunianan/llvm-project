#ifndef LLVM_LIB_TARGET_SIMULATOR_SIMULATORINSTRINFO_H
#define LLVM_LIB_TARGET_SIMULATOR_SIMULATORINSTRINFO_H

#include "SimulatorRegisterInfo.h"
#include "MCTargetDesc/SimulatorInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "SimulatorGenInstrInfo.inc"

namespace llvm {

class SimulatorSubtarget;

class SimulatorInstrInfo : public SimulatorGenInstrInfo {
public:
  SimulatorInstrInfo();

};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_SIMULATOR_SIMULATORINSTRINFO_H