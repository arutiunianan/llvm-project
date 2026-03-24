#include "SimulatorSubtarget.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "simulator-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "SimulatorGenSubtargetInfo.inc"

SimulatorSubtarget::SimulatorSubtarget(const StringRef &CPU, const StringRef &TuneCPU,
                           const StringRef &FS, const TargetMachine &TM)
    : SimulatorGenSubtargetInfo(TM.getTargetTriple(), CPU, TuneCPU, FS) {}