#include "SimulatorTargetMachine.h"
#include "Simulator.h"
#include "TargetInfo/SimulatorTargetInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"
#include <optional>

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeSimulatorTarget() {
  SIMULATOR_DUMP_CYAN
  RegisterTargetMachine<SimulatorTargetMachine> A(getTheSimulatorTarget());
}

SimulatorTargetMachine::SimulatorTargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   std::optional<Reloc::Model> RM,
                                   std::optional<CodeModel::Model> CM,
                                   CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, "e-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-n32",
                               TT, CPU, FS, Options, Reloc::Static,
                               getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  SIMULATOR_DUMP_CYAN
  initAsmInfo();
}

namespace {

class SimulatorPassConfig : public TargetPassConfig {
public:
  SimulatorPassConfig(SimulatorTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  SimulatorTargetMachine &getSimulatorTargetMachine() const {
    return getTM<SimulatorTargetMachine>();
  }

  bool addInstSelector() override {
    SIMULATOR_DUMP_CYAN
    addPass(createSimulatorISelDag(getSimulatorTargetMachine(), getOptLevel()));
    return false;
  }
};

} // end anonymous namespace

TargetPassConfig *SimulatorTargetMachine::createPassConfig(PassManagerBase &PM) {
  SIMULATOR_DUMP_CYAN
  return new SimulatorPassConfig(*this, PM);
}

TargetLoweringObjectFile *SimulatorTargetMachine::getObjFileLowering() const {
  SIMULATOR_DUMP_CYAN
  return TLOF.get();
}