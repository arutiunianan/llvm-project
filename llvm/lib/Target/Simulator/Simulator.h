#ifndef LLVM_LIB_TARGET_Simulator_Simulator_H
#define LLVM_LIB_TARGET_Simulator_Simulator_H

#include "llvm/Target/TargetMachine.h"

namespace llvm {
class SimulatorTargetMachine;
class FunctionPass;
class SimulatorSubtarget;
class AsmPrinter;
class InstructionSelector;
class MCInst;
class MCOperand;
class MachineInstr;
class MachineOperand;
class PassRegistry;

bool lowerSimulatorMachineInstrToMCInst(const MachineInstr *MI, MCInst &OutMI,
                                  AsmPrinter &AP);
bool LowerSimulatorMachineOperandToMCOperand(const MachineOperand &MO,
                                       MCOperand &MCOp, const AsmPrinter &AP);

FunctionPass *createSimulatorISelDag(SimulatorTargetMachine &TM, CodeGenOptLevel OptLevel);

} // namespace llvm

#endif // LLVM_LIB_TARGET_Simulator_Simulator_H