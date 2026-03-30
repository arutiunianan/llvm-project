#ifndef LLVM_LIB_TARGET_SIMULATOR_MCTARGETDESC_SIMULATORMCTARGETDESC_H
#define LLVM_LIB_TARGET_SIMULATOR_MCTARGETDESC_SIMULATORMCTARGETDESC_H

namespace llvm {
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;

MCCodeEmitter *createSimulatorMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx);
} // namespace llvm

#define GET_REGINFO_ENUM
#include "SimulatorGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "SimulatorGenInstrInfo.inc"

#endif // LLVM_LIB_TARGET_SIMULATOR_MCTARGETDESC_SIMULATORMCTARGETDESC_H