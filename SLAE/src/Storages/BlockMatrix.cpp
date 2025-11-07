#include "BlockMatrix.h"
#include <stdexcept>
#include <algorithm>

BlockMatrix::BlockMatrix(
    const std::vector<double>& di,
    const std::vector<double>& gg,
    const std::vector<int>& idi,
    const std::vector<int>& ijg,
    const std::vector<int>& ig,
    const std::vector<int>& jg
) : _diagonal(di), _values(gg), _diagonalIndexes(idi),
_offDiagonalIndexes(ijg), _rowIndex(ig), _columnIndex(jg) {
}

int BlockMatrix::Size() const {
    return static_cast<int>(_diagonalIndexes.size()) - 1;
}

std::vector<double> BlockMatrix::GetBlock(int i, int j) const {
    return GetBlockData(i, j);
}

ComplexVector BlockMatrix::MultiplyOn(const ComplexVector& vector) const {
    const auto& x = vector.GetValues();
    std::vector<double> y(vector.Length(), 0.0);

    int systemSize = vector.Length() / 2;

    for (int i = 0; i < systemSize; ++i) {
        auto diagBlock = GetBlockData(i, i);

        // Extract x block for current row
        double x0 = x[i * 2];
        double x1 = x[i * 2 + 1];

        // Multiply diagonal block with x block
        y[i * 2] += diagBlock[0] * x0;
        y[i * 2 + 1] += diagBlock[0] * x1;

        if (diagBlock.size() == 2) {
            y[i * 2] -= diagBlock[1] * x1;
            y[i * 2 + 1] += diagBlock[1] * x0;
        }

        for (int j = _rowIndex[i]; j < _rowIndex[i + 1]; ++j) {
            int k = _columnIndex[j];
            auto offDiagBlock = GetBlockData(i, j);

            // Extract x blocks for current and connected nodes
            double xk0 = x[k * 2];
            double xk1 = x[k * 2 + 1];

            // Multiply off-diagonal block with xk and add to yi
            y[i * 2] += offDiagBlock[0] * xk0;
            y[i * 2 + 1] += offDiagBlock[0] * xk1;

            if (offDiagBlock.size() == 2) {
                y[i * 2] -= offDiagBlock[1] * xk1;
                y[i * 2 + 1] += offDiagBlock[1] * xk0;
            }

            // Multiply off-diagonal block with xi and add to yk
            y[k * 2] += offDiagBlock[0] * x0;
            y[k * 2 + 1] += offDiagBlock[0] * x1;

            if (offDiagBlock.size() == 2) {
                y[k * 2] -= offDiagBlock[1] * x1;
                y[k * 2 + 1] += offDiagBlock[1] * x0;
            }
        }
    }

    return ComplexVector(y);
}

BlockMatrix BlockMatrix::Clone() const {
    return BlockMatrix(_diagonal, _values, _diagonalIndexes, _offDiagonalIndexes, _rowIndex, _columnIndex);
}

void BlockMatrix::BlockMultiply(const std::vector<double>& a, const std::vector<double>& x, std::vector<double>& resultMemory, int resultOffset) const {
    resultMemory[resultOffset] += a[0] * x[0];
    resultMemory[resultOffset + 1] += a[0] * x[1];

    if (a.size() == 2) {
        resultMemory[resultOffset] -= a[1] * x[1];
        resultMemory[resultOffset + 1] += a[1] * x[0];
    }
}

std::vector<double> BlockMatrix::GetBlockData(int i, int j) const {
    int currentBlockIndex;
    int length;

    if (i == j) {
        currentBlockIndex = _diagonalIndexes[i];
        length = GetDiagonalBlockSize(i);

        return std::vector<double>(_diagonal.begin() + currentBlockIndex, _diagonal.begin() + currentBlockIndex + length);
    }

    currentBlockIndex = _offDiagonalIndexes[j];
    length = GetOffDiagonalBlockSize(j);

    return std::vector<double>(_values.begin() + currentBlockIndex, _values.begin() + currentBlockIndex + length);
}

int BlockMatrix::GetDiagonalBlockSize(int offset) const {
    return _diagonalIndexes[offset + 1] - _diagonalIndexes[offset];
}

int BlockMatrix::GetOffDiagonalBlockSize(int offset) const {
    return _offDiagonalIndexes[offset + 1] - _offDiagonalIndexes[offset];
}