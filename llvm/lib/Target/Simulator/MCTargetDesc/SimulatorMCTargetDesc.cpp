#include "MCTargetDesc/SimulatorInfo.h"
#include "SimulatorMCAsmInfo.h"
#include "TargetInfo/SimulatorTargetInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"

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

static MCAsmInfo *createSimulatorMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT,
                                     const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new SimulatorELFMCAsmInfo(TT);
  unsigned SP = MRI.getDwarfRegNum(Simulator::R1, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

extern "C" void LLVMInitializeSimulatorTargetMC() {
  Target &TheSimulatorTarget = getTheSimulatorTarget();
  RegisterMCAsmInfoFn X(TheSimulatorTarget, createSimulatorMCAsmInfo);
  TargetRegistry::RegisterMCRegInfo(TheSimulatorTarget, createSimulatorMCRegisterInfo);
  TargetRegistry::RegisterMCInstrInfo(TheSimulatorTarget, createSimulatorMCInstrInfo);
  TargetRegistry::RegisterMCSubtargetInfo(TheSimulatorTarget,
                                          createSimulatorMCSubtargetInfo);
}