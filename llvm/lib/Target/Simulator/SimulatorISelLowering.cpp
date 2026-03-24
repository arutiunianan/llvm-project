#include "SimulatorISelLowering.h"
#include "SimulatorRegisterInfo.h"
#include "SimulatorSubtarget.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFunction.h"

#define DEBUG_TYPE "Simulator-lower"

using namespace llvm;

SimulatorTargetLowering::SimulatorTargetLowering(const TargetMachine &TM,
                                     const SimulatorSubtarget &STI)
    : TargetLowering(TM), STI(STI) {
  addRegisterClass(MVT::i32, &Simulator::GPRRegClass);
}

const char *SimulatorTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch (Opcode) {
  case SimulatorISD::CALL:
    return "SimulatorISD::CALL";
  case SimulatorISD::RET:
    return "SimulatorISD::RET";
  }
  return nullptr;
}