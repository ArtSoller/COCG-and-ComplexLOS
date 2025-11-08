#include "ComplDiagPrecondFactory.h"

ComplexDiagonalPreconditioner ComplexDiagonalPreconditionerFactory::CreatePreconditioner(const BlockMatrix& matrix) const {
    return ComplexDiagonalPreconditioner(matrix);
}