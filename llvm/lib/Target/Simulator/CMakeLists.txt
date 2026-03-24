add_llvm_component_group(Simulator)

set(LLVM_TARGET_DEFINITIONS Simulator.td)

tablegen(LLVM SimulatorGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM SimulatorGenInstrInfo.inc -gen-instr-info)

add_public_tablegen_target(SimulatorCommonTableGen)

add_llvm_target(SimulatorCodeGen
    SimulatorTargetMachine.cpp
    SimulatorRegisterInfo.cpp
    SimulatorInstrInfo.cpp

  LINK_COMPONENTS
  CodeGen
  Core
  Support
  Target
  SimulatorInfo

  ADD_TO_COMPONENT
  Simulator
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)