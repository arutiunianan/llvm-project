#include "SimulatorRegisterInfo.h"
#include "SimulatorFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "SimulatorGenRegisterInfo.inc"

SimulatorRegisterInfo::SimulatorRegisterInfo() : SimulatorGenRegisterInfo(Simulator::R0) {}