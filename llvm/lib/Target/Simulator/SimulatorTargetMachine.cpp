#include "SimulatorTargetMachine.h"
#include "TargetInfo/SimulatorTargetInfo.h"

#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Transforms/Scalar.h"
#include <optional>

using namespace llvm;


extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSimulatorTarget() {
  RegisterTargetMachine<SimulatorTargetMachine> A(getTheSimulatorTarget());
}

static std::string computeDataLayout(const Triple &TT, StringRef CPU,
                                     const TargetOptions &Options,
                                     bool IsLittle) {
  std::string Ret = "e-m:e-p:64:64-i64:64-i128:128-n32:64-S64";
  return Ret;
}

static Reloc::Model getEffectiveRelocModel(bool JIT,
                                           std::optional<Reloc::Model> RM) {
  if (!RM || JIT)
     return Reloc::Static;
  return *RM;
}

SimulatorTargetMachine::SimulatorTargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         std::optional<Reloc::Model> RM,
                                         std::optional<CodeModel::Model> CM,
                                         CodeGenOptLevel OL, bool JIT,
                                         bool IsLittle)
    : CodeGenTargetMachineImpl(T, computeDataLayout(TT, CPU, Options, IsLittle), TT,
                               CPU, FS, Options, getEffectiveRelocModel(JIT, RM),
                               getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()) {
  initAsmInfo();
}

SimulatorTargetMachine::SimulatorTargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         std::optional<Reloc::Model> RM,
                                         std::optional<CodeModel::Model> CM,
                                         CodeGenOptLevel OL, bool JIT)
    : SimulatorTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL, JIT, true) {}

TargetPassConfig *SimulatorTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new TargetPassConfig(*this, PM);
}

namespace {

class SimulatorPassConfig : public TargetPassConfig {
public:
  SimulatorPassConfig(SimulatorTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  bool addInstSelector() override {
    return false;
  }
};

} // end anonymous namespace

TargetPassConfig *SimulatorTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new SimulatorPassConfig(*this, PM);
}