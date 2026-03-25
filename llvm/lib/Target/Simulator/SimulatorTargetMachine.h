#ifndef LLVM_LIB_TARGET_SIMULATOR_SIMULATORTARGETMACHINE_H
#define LLVM_LIB_TARGET_SIMULATOR_SIMULATORTARGETMACHINE_H

#include "SimulatorSubtarget.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include <optional>

namespace llvm {
extern Target TheSimulatorTarget;

class SimulatorTargetMachine : public CodeGenTargetMachineImpl {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  SimulatorSubtarget Subtarget;

public:
  SimulatorTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, const TargetOptions &Options,
                   std::optional<Reloc::Model> RM,
                   std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                   bool JIT);

  const SimulatorSubtarget *getSubtargetImpl(const Function &) const override {
    SIMULATOR_DUMP_CYAN
    return &Subtarget;
  }
  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  TargetLoweringObjectFile *getObjFileLowering() const override;
};
} // end namespace llvm

#endif // LLVM_LIB_TARGET_SIMULATOR_SIMULATORTARGETMACHINE_H