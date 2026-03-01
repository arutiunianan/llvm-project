add_llvm_component_library(LLVMSimulatorDesc
  SimulatorMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  Support
  SimulatorInfo

  ADD_TO_COMPONENT
  Simulator
)