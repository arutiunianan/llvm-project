add_llvm_component_group(Simulator)

add_llvm_target(SimulatorCodeGen
    SimulatorTargetMachine.cpp

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