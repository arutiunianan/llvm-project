#ifndef LLVM_LIB_TARGET_Simulator_Simulator_H
#define LLVM_LIB_TARGET_Simulator_Simulator_H

#include "llvm/Target/TargetMachine.h"

namespace llvm {
class SimulatorTargetMachine;
class FunctionPass;

FunctionPass *createSimulatorISelDag(SimulatorTargetMachine &TM, CodeGenOptLevel OptLevel);

} // namespace llvm

#endif // LLVM_LIB_TARGET_Simulator_Simulator_H