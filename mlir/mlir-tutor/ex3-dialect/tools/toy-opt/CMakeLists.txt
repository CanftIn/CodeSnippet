message("${CMAKE_CURRENT_SOURCE_DIR}: " ${CMAKE_CURRENT_SOURCE_DIR})

add_mlir_tool(ex3-opt toy-opt.cpp)
target_link_libraries(ex3-opt
  PRIVATE Toy
  MLIRIR MLIRParser MLIRSupport
  MLIROptLib        # 对应 #include "mlir/Tools/mlir-opt/MlirOptMain.h"
  MLIRFuncDialect   # 对应 #include "mlir/Dialect/Func/IR/FuncOps.h"
  MLIRTransforms    # 对应 #include "mlir/Transforms/Passes.h"
)
