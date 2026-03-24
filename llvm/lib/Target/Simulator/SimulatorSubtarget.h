#ifndef LLVM_LIB_TARGET_SIMULATOR_SIMULATORSUBTARGET_H
#define LLVM_LIB_TARGET_SIMULATOR_SIMULATORSUBTARGET_H

#include "SimulatorISelLowering.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "SimulatorGenSubtargetInfo.inc"

namespace llvm {

class SimulatorSubtarget : public SimulatorGenSubtargetInfo {
  SimulatorTargetLowering TLInfo;
public:
  SimulatorSubtarget(const Triple &TT, const std::string &CPU, const std::string &FS,
               const TargetMachine &TM);

  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);

  const SimulatorTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_SIMULATOR_SIMULATORSUBTARGET_H