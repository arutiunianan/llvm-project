#ifndef LLVM_LIB_TARGET_ULATOR_SIMULATORFRAMELOWERING_H
#define LLVM_LIB_TARGET_SIMULATOR_SIMULATORFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
class SimulatorSubtarget;

class SimulatorFrameLowering : public TargetFrameLowering {
public:
  SimulatorFrameLowering(const SimulatorSubtarget &STI)
      : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(4), 0),
        STI(STI) {}

  void emitPrologue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override {}
  void emitEpilogue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override {}

  bool hasFPImpl(const MachineFunction &MF) const override { return false; }

private:
  const SimulatorSubtarget &STI;
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_SIMULATOR_SIMULATORFRAMELOWERING_H