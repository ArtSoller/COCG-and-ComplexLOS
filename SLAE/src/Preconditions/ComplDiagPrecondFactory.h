#pragma once
#include "ComplDiagPreconditioner.h"

class ComplexDiagonalPreconditionerFactory {
public:
    ComplexDiagonalPreconditioner CreatePreconditioner(const BlockMatrix& matrix) const;
};
