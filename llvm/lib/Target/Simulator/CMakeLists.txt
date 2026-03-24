add_llvm_component_group(Simulator)

set(LLVM_TARGET_DEFINITIONS Simulator.td)

tablegen(LLVM SimulatorGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM SimulatorGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM SimulatorGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM SimulatorGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM SimulatorGenCallingConv.inc -gen-callingconv)
tablegen(LLVM SimulatorGenAsmWriter.inc -gen-asm-writer)

add_public_tablegen_target(SimulatorCommonTableGen)

add_llvm_target(SimulatorCodeGen
    SimulatorTargetMachine.cpp
    SimulatorRegisterInfo.cpp
    SimulatorInstrInfo.cpp
    SimulatorSubtarget.cpp
    SimulatorAsmPrinter.cpp
    SimulatorISelDagToDag.cpp
    SimulatorISelLowering.cpp
    SimulatorMCInstLower.cpp

  LINK_COMPONENTS
  CodeGen
  Core
  Support
  Target
  SimulatorInfo
  AsmPrinter

  ADD_TO_COMPONENT
  Simulator
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)