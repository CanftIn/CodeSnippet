#ifndef TOY_OPS_H
#define TOY_OPS_H

#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Builders.h"

#include "toy/ToyDialect.h"
#include "mlir/Interfaces/InferTypeOpInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Interfaces/ControlFlowInterfaces.h"
#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/IR/RegionKindInterface.h"

#define GET_OP_CLASSES
#include "toy/Toy.h.inc"

#endif  // TOY_OPS_H
