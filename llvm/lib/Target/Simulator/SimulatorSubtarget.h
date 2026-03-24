#ifndef LLVM_LIB_TARGET_SIMULATOR_SIMULATORSUBTARGET_H
#define LLVM_LIB_TARGET_SIMULATOR_SIMULATORSUBTARGET_H

#include "SimulatorFrameLowering.h"
#include "SimulatorISelLowering.h"
#include "SimulatorRegisterInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "SimulatorGenSubtargetInfo.inc"

namespace llvm {

class SimulatorSubtarget : public SimulatorGenSubtargetInfo {
  SimulatorTargetLowering TLInfo;
  SimulatorFrameLowering FrameLowering;
  SimulatorRegisterInfo RegInfo;

public:
  SimulatorSubtarget(const Triple &TT, const std::string &CPU, const std::string &FS,
               const TargetMachine &TM);

  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);

  const SimulatorTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }
  const SimulatorFrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }
  const SimulatorRegisterInfo *getRegisterInfo() const override {
    return &RegInfo;
  }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_SIMULATOR_SIMULATORSUBTARGET_H