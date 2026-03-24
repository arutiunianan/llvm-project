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

class SimulatorTargetLowering : public TargetLowering {
public:
  explicit SimulatorTargetLowering(const TargetMachine &TM, const SimulatorSubtarget &STI);

  /// This method returns the name of a target specific DAG node.
  const char *getTargetNodeName(unsigned Opcode) const override;

  SimulatorSubtarget const &getSubtarget() const { return STI; }

private:
  const SimulatorSubtarget &STI;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_SIMULATOR_SIMULATORISELLOWERING_H