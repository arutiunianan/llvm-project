#include "MCTargetDesc/SimulatorInfo.h"
#include "TargetInfo/SimulatorTargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "SimulatorGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "SimulatorGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "SimulatorGenSubtargetInfo.inc"

static MCRegisterInfo *createSimulatorMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitSimulatorMCRegisterInfo(X, Simulator::R0);
  return X;
}

static MCInstrInfo *createSimulatorMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitSimulatorMCInstrInfo(X);
  return X;
}

static MCSubtargetInfo *createSimulatorMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  return createSimulatorMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

extern "C" void LLVMInitializeSimulatorTargetMC() {
  Target &TheSimulatorTarget = getTheSimulatorTarget();
  TargetRegistry::RegisterMCRegInfo(TheSimulatorTarget, createSimulatorMCRegisterInfo);
  TargetRegistry::RegisterMCInstrInfo(TheSimulatorTarget, createSimulatorMCInstrInfo);
  TargetRegistry::RegisterMCSubtargetInfo(TheSimulatorTarget,
                                          createSimulatorMCSubtargetInfo);
}