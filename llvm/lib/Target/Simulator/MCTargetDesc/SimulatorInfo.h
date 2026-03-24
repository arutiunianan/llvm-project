
#define LLVM_LIB_TARGET_SIMULATOR_MCTARGETDESC_SIMULATORINFO_H

#include "llvm/MC/MCInstrDesc.h"

namespace llvm {

namespace SimulatorOp {
enum OperandType : unsigned {
  OPERAND_SIMM16 = MCOI::OPERAND_FIRST_TARGET,
};
} // namespace SimulatorOp

} // end namespace llvm

#endif