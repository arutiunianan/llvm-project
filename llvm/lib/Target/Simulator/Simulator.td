include "llvm/Target/Target.td"
include "SimulatorRegisterInfo.td"
include "SimulatorInstrInfo.td"

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

def SimulatorInstrInfo : InstrInfo;
def Simulator : Target {
  let InstructionSet = SimulatorInstrInfo;
}