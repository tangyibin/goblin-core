include_directories( ${CMAKE_CURRENT_BINARY_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/.. )

add_llvm_library(LLVMGC64Info
  GC64TargetInfo.cpp
  )

add_dependencies(LLVMGC64Info GC64CommonTableGen)
