include "llvm/Target/Target.td"
include "SimulatorRegisterInfo.td"
include "SimulatorInstrInfo.td"

def SimulatorInstrInfo : InstrInfo;
def Simulator : Target {
  let InstructionSet = SimulatorInstrInfo;
}