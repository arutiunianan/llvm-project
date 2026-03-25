#include "SimulatorSubtarget.h"
#include "Simulator.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "simulator-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "SimulatorGenSubtargetInfo.inc"

SimulatorSubtarget::SimulatorSubtarget(const Triple &TT, const std::string &CPU,
                           const std::string &FS, const TargetMachine &TM)
    : SimulatorGenSubtargetInfo(TT, CPU, /*TuneCPU=*/CPU, FS), TLInfo(TM, *this),
      FrameLowering(*this), InstrInfo() {
  SIMULATOR_DUMP_CYAN
}