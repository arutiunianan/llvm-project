#ifndef LLVM_LIB_TARGET_SIMULATOR_SIMULATORISELLOWERING_H
#define LLVM_LIB_TARGET_SIMULATOR_SIMULATORISELLOWERING_H

#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

class SimulatorSubtarget;
class SimulatorTargetMachine;

namespace SimulatorISD {

enum NodeType : unsigned {
  // Start the numbering where the builtin ops and target ops leave off.
  FIRST_NUMBER = ISD::BUILTIN_OP_END,
  RET,
  CALL,
  BR_CC,
};

} // namespace SimulatorISD

} // end namespace llvm

#endif // LLVM_LIB_TARGET_SIMULATOR_SIMULATORISELLOWERING_H