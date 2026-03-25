#include "MCTargetDesc/SimulatorMCTargetDesc.h"
#include "Simulator.h"
#include "SimulatorISelLowering.h"
#include "SimulatorTargetMachine.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "simulator-isel"

namespace {

class SimulatorDAGToDAGISel : public SelectionDAGISel {

public:
  static char ID;
  SimulatorDAGToDAGISel() = delete;
  explicit SimulatorDAGToDAGISel(SimulatorTargetMachine &TM, CodeGenOptLevel OptLevel)
      : SelectionDAGISel(TM, OptLevel) {
    SIMULATOR_DUMP_RED
  }

  bool runOnMachineFunction(MachineFunction &MF) override {
    SIMULATOR_DUMP_RED
    return SelectionDAGISel::runOnMachineFunction(MF);
  }

  void Select(SDNode *N) override;

#include "SimulatorGenDAGISel.inc"
};
class SimulatorDAGToDAGISelLegacy : public SelectionDAGISelLegacy {
public:
  static char ID;

  SimulatorDAGToDAGISelLegacy(SimulatorTargetMachine &TM, CodeGenOptLevel OptLevel)
      : SelectionDAGISelLegacy(
            ID, std::make_unique<SimulatorDAGToDAGISel>(TM, OptLevel)){SIMULATOR_DUMP_RED}

        StringRef getPassName() const override {
    return "Simulator DAG->DAG Pattern Instruction Selection";
  }
};
} // end anonymous namespace

char SimulatorDAGToDAGISelLegacy::ID = 0;

/// This pass converts a legalized DAG into a Simulator-specific DAG, ready for
/// instruction scheduling.
FunctionPass *llvm::createSimulatorISelDag(SimulatorTargetMachine &TM,
                                     CodeGenOptLevel OptLevel) {
  SIMULATOR_DUMP_RED
  return new SimulatorDAGToDAGISelLegacy(TM, OptLevel);
}

void SimulatorDAGToDAGISel::Select(SDNode *Node) {
  SIMULATOR_DUMP_RED
  if (Node->isMachineOpcode()) {
    Node->setNodeId(-1);
    return;
  }
  SDLoc DL(Node);
  SelectCode(Node);
}