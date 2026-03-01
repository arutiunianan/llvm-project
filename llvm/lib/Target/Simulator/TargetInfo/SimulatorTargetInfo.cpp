#include "TargetInfo/SimulatorTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheSimulatorTarget() {
  static Target TheSimulatorTarget;
  return TheSimulatorTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSimulatorTargetInfo() {
  RegisterTarget<Triple::simulator> X(getTheSimulatorTarget(), "simulator", "Simulator 64",
                                   "SIMULATOR");
}