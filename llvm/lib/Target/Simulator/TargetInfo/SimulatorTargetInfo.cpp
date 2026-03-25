#include "TargetInfo/SimulatorTargetInfo.h"
#include "Simulator.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheSimulatorTarget() {
  SIMULATOR_DUMP_YELLOW
  static Target TheSimulatorTarget;
  return TheSimulatorTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSimulatorTargetInfo() {
  SIMULATOR_DUMP_YELLOW
  RegisterTarget<Triple::simulator> X(getTheSimulatorTarget(), "simulator",
                                "Simulatorulator target for LLVM course", "SIMULATOR");
}