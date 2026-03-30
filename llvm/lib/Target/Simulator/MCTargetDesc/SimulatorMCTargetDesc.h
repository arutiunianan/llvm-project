#ifndef LLVM_LIB_TARGET_SIMULATOR_MCTARGETDESC_SIMULATORMCTARGETDESC_H
#define LLVM_LIB_TARGET_SIMULATOR_MCTARGETDESC_SIMULATORMCTARGETDESC_H

namespace llvm {
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;class MCAsmBackend;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;
class Target;

MCCodeEmitter *createSimulatorMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx);
MCAsmBackend *createSimulatorAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                  const MCRegisterInfo &MRI,
                                  const MCTargetOptions &Options);
} // namespace llvm

#define GET_REGINFO_ENUM
#include "SimulatorGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "SimulatorGenInstrInfo.inc"

#endif // LLVM_LIB_TARGET_SIMULATOR_MCTARGETDESC_SIMULATORMCTARGETDESC_H