#include "MCTargetDesc/SimulatorInfo.h"
#include "Simulator.h"
#include "SimulatorInstPrinter.h"
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
  SIMULATOR_DUMP_MAGENTA
  MCRegisterInfo *X = new MCRegisterInfo();
  InitSimulatorMCRegisterInfo(X, Simulator::R0);
  return X;
}

static MCInstrInfo *createSimulatorMCInstrInfo() {
  SIMULATOR_DUMP_MAGENTA
  MCInstrInfo *X = new MCInstrInfo();
  InitSimulatorMCInstrInfo(X);
  return X;
}

static MCSubtargetInfo *createSimulatorMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  SIMULATOR_DUMP_MAGENTA
  return createSimulatorMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

static MCAsmInfo *createSimulatorMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT,
                                     const MCTargetOptions &Options) {
  SIMULATOR_DUMP_MAGENTA
  MCAsmInfo *MAI = new SimulatorELFMCAsmInfo(TT);
  unsigned SP = MRI.getDwarfRegNum(Simulator::R1, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCInstPrinter *createSimulatorMCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  SIMULATOR_DUMP_MAGENTA
  return new SimulatorInstPrinter(MAI, MII, MRI);
}

// We need to define this function for linking succeed
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSimulatorTargetMC() {
  SIMULATOR_DUMP_MAGENTA
  Target &TheSimulatorTarget = getTheSimulatorTarget();
  RegisterMCAsmInfoFn X(TheSimulatorTarget, createSimulatorMCAsmInfo);
  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheSimulatorTarget, createSimulatorMCRegisterInfo);
  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheSimulatorTarget, createSimulatorMCInstrInfo);
  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheSimulatorTarget,
                                          createSimulatorMCSubtargetInfo);
  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheSimulatorTarget, createSimulatorMCInstPrinter);
  // Register the MC Code Emitter.
  TargetRegistry::RegisterMCCodeEmitter(TheSimulatorTarget, createSimulatorMCCodeEmitter);
  // Register the asm backend.
  TargetRegistry::RegisterMCAsmBackend(TheSimulatorTarget, createSimulatorAsmBackend);
}