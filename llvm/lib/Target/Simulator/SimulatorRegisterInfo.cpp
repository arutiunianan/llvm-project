#include "SimulatorRegisterInfo.h"
#include "SimulatorFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "SimulatorGenRegisterInfo.inc"

SimulatorRegisterInfo::SimulatorRegisterInfo() : SimulatorGenRegisterInfo(Simulator::R0) {}

const MCPhysReg *
SimulatorRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_Simulator_SaveList;
}

BitVector SimulatorRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  SimulatorFrameLowering const *TFI = getFrameLowering(MF);

  BitVector Reserved(getNumRegs());
  Reserved.set(Simulator::R1);

  if (TFI->hasFP(MF)) {
    Reserved.set(Simulator::R2);
  }
  return Reserved;
}

bool SimulatorRegisterInfo::requiresRegisterScavenging(
    const MachineFunction &MF) const {
  return false;
}

bool SimulatorRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                          int SPAdj, unsigned FIOperandNum,
                                          RegScavenger *RS) const {
  assert(SPAdj == 0 && "Unexpected non-zero SPAdj value");

  MachineInstr &MI = *II;
  MachineFunction &MF = *MI.getParent()->getParent();
  DebugLoc DL = MI.getDebugLoc();

  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();
  Register FrameReg;
  int Offset = getFrameLowering(MF)
                   ->getFrameIndexReference(MF, FrameIndex, FrameReg)
                   .getFixed();
  Offset += MI.getOperand(FIOperandNum + 1).getImm();

  if (!isInt<16>(Offset)) {
    llvm_unreachable("");
  }

  MI.getOperand(FIOperandNum).ChangeToRegister(FrameReg, false, false, false);
  MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);
  return false;
}

Register SimulatorRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  const TargetFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? Simulator::R2 : Simulator::R1;
}

const uint32_t *
SimulatorRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                      CallingConv::ID CC) const {
  return CSR_Simulator_RegMask;
}