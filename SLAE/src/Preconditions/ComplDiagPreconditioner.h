#pragma once
#include "../Storages/BlockMatrix.h"
#include "../Storages/ComplexVector.h"
#include <vector>
#include <memory>

class ComplexDiagonalPreconditioner {
private:
    BlockMatrix _decomposedMatrix;

public:
    explicit ComplexDiagonalPreconditioner(const BlockMatrix& matrix);

    ComplexVector MultiplyOn(const ComplexVector& vector) const;

private:
    static ComplexVector EvaluateInverseDiagonal(const BlockMatrix& matrix);
};