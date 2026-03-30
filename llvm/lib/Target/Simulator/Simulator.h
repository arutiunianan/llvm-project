#ifndef LLVM_LIB_TARGET_Simulator_Simulator_H
#define LLVM_LIB_TARGET_Simulator_Simulator_H

#include "MCTargetDesc/SimulatorMCTargetDesc.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"

/*#define SIMULATOR_DUMP(Color)                                                  \
  {                                                                            \
    llvm::errs().changeColor(Color)                                            \
        << __func__ << "\n\t\t" << __FILE__ << ":" << __LINE__ << "\n";        \
    llvm::errs().changeColor(llvm::raw_ostream::WHITE);                        \
  }*/
#define SIMULATOR_DUMP(Color) {}

#define SIMULATOR_DUMP_RED SIMULATOR_DUMP(llvm::raw_ostream::RED)
#define SIMULATOR_DUMP_GREEN SIMULATOR_DUMP(llvm::raw_ostream::GREEN)
#define SIMULATOR_DUMP_YELLOW SIMULATOR_DUMP(llvm::raw_ostream::YELLOW)
#define SIMULATOR_DUMP_CYAN SIMULATOR_DUMP(llvm::raw_ostream::CYAN)
#define SIMULATOR_DUMP_MAGENTA SIMULATOR_DUMP(llvm::raw_ostream::MAGENTA)
#define SIMULATOR_DUMP_WHITE SIMULATOR_DUMP(llvm::raw_ostream::WHITE)
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