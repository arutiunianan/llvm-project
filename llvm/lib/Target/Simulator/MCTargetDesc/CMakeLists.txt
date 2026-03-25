add_llvm_component_library(LLVMSimulatorDesc
  SimulatorMCTargetDesc.cpp
  SimulatorMCAsmInfo.cpp
  SimulatorInstPrinter.cpp

  LINK_COMPONENTS
  MC
  Support
  SimulatorInfo

  ADD_TO_COMPONENT
  Simulator
 )