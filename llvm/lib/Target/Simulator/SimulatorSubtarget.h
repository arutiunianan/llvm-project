#ifndef LLVM_LIB_TARGET_SIMULATOR_SIMULATORSUBTARGET_H
#define LLVM_LIB_TARGET_SIMULATOR_SIMULATORSUBTARGET_H

#include "SimulatorFrameLowering.h"
#include "SimulatorISelLowering.h"
#include "SimulatorInstrInfo.h"
#include "SimulatorRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "SimulatorGenSubtargetInfo.inc"

namespace llvm {

class SimulatorSubtarget : public SimulatorGenSubtargetInfo {
  SimulatorTargetLowering TLInfo;
  SimulatorFrameLowering FrameLowering;
  SimulatorRegisterInfo RegInfo;
  SimulatorInstrInfo InstrInfo;
  SelectionDAGTargetInfo TSInfo;

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
  const SimulatorInstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const SelectionDAGTargetInfo *getSelectionDAGInfo() const override {
    return &TSInfo;
  }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_SIMULATOR_SIMULATORSUBTARGET_H