#include "ComplDiagPreconditioner.h"
#include <vector>

ComplexDiagonalPreconditioner::ComplexDiagonalPreconditioner(const BlockMatrix& matrix)
    : _decomposedMatrix(
        EvaluateInverseDiagonal(matrix).GetValues(), // inverseDiagonal.Values
        std::vector<double>(),                      // []
        matrix._diagonalIndexes,                // matrix.DiagonalIndexes
        std::vector<int>(),                         // []
        std::vector<int>(matrix.Size() + 1, 0),     // new int[matrix.Size + 1]
        std::vector<int>()                          // []
    ) {
}

ComplexVector ComplexDiagonalPreconditioner::MultiplyOn(const ComplexVector& vector) const {
    return _decomposedMatrix.MultiplyOn(vector);
}

ComplexVector ComplexDiagonalPreconditioner::EvaluateInverseDiagonal(const BlockMatrix& matrix) {
    auto n = matrix.Size();
    auto resultMemory = ComplexVector(matrix._diagonalIndexes.size());
    auto& resultValues = const_cast<std::vector<double>&>(resultMemory.GetValues());

    int offset = 0;
    for (int i = 0; i < n; ++i) {
        auto block = matrix(i, i);
        auto length = block.size();

        double det = block[0] * block[0];
        if (block.size() == 2) {
            det += block[1] * block[1];
            resultValues[offset + 1] = -block[1] / det;
        }

        resultValues[offset] = block[0] / det;
        offset += length;
    }

    return resultMemory;
}