add_llvm_component_library(LLVMSimulatorInfo
  SimulatorTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  Simulator
)