#include "MCTargetDesc/SimulatorInfo.h"
#include "TargetInfo/SimulatorTargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "SimulatorGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "SimulatorGenInstrInfo.inc"

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

extern "C" void LLVMInitializeSimulatorTargetMC() {
  Target &TheSimulatorTarget = getTheSimulatorTarget();
  TargetRegistry::RegisterMCRegInfo(TheSimulatorTarget, createSimulatorMCRegisterInfo);
  TargetRegistry::RegisterMCInstrInfo(TheSimulatorTarget, createSimulatorMCInstrInfo);
}