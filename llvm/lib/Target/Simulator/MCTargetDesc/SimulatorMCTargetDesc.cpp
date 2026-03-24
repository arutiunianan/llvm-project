#include "TargetInfo/SimulatorTargetInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "SimulatorGenRegisterInfo.inc"

static MCRegisterInfo *createSimulatorMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitSimulatorMCRegisterInfo(X, Simulator::R0);
  return X;
}

extern "C" void LLVMInitializeSimulatorTargetMC() {
  Target &TheSimulatorTarget = getTheSimulatorTarget();
  TargetRegistry::RegisterMCRegInfo(TheSimulatorTarget, createSimulatorMCRegisterInfo);
}