#include "BlockMatrix.h"

BlockMatrix::BlockMatrix(const std::vector<double>& di,
    const std::vector<double>& gg,
    const std::vector<int>& idi,
    const std::vector<int>& ijg,
    const std::vector<int>& ig,
    const std::vector<int>& jg)
    : _diagonal(di), _values(gg), _diagonalIndexes(idi),
    _offDiagonalIndexes(ijg), _rowIndex(ig), _columnIndex(jg) {
}

int BlockMatrix::Size() const {
    return _diagonalIndexes.size() - 1;
}

std::span<const double> BlockMatrix::operator()(int i, int j) const {
    return GetBlockData(i, j);
}

ComplexVector BlockMatrix::MultiplyOn(const ComplexVector& vector, ComplexVector* resultMemory) const {
    if (resultMemory == nullptr) {
        ComplexVector tempResult(vector.Length());
        return BlockMatrixMultiply(vector, tempResult);
    }
    else {
        return BlockMatrixMultiply(vector, *resultMemory);
    }
}

BlockMatrix BlockMatrix::Clone() const {
    return BlockMatrix(_diagonal, _values, _diagonalIndexes,
        _offDiagonalIndexes, _rowIndex, _columnIndex);
}

ComplexVector BlockMatrix::BlockMatrixMultiply(const ComplexVector& vector, ComplexVector& resultMemory) const {
    if (vector.Length() % 2 != 0) {
        throw std::invalid_argument("Vector length must be even");
    }

    auto systemSize = vector.Length() / 2;
    const auto& x = vector.GetValues();
    auto& y = const_cast<std::vector<double>&>(resultMemory.GetValues());

    for (int i = 0; i < systemSize; ++i) {
        auto diagBlock = GetBlockData(i, i);
        std::span<const double> xBlock(x.data() + i * 2, 2);
        std::span<double> yBlock(y.data() + i * 2, 2);

        BlockMultiply(diagBlock, xBlock, yBlock);

        for (int j = _rowIndex[i]; j < _rowIndex[i + 1]; ++j) {
            auto k = _columnIndex[j];
            auto offDiagBlock = GetBlockData(i, j);
            std::span<const double> xk(x.data() + k * 2, 2);
            std::span<double> yk(y.data() + k * 2, 2);

            BlockMultiply(offDiagBlock, xk, yBlock);
            BlockMultiply(offDiagBlock, xBlock, yk);
        }
    }

    return resultMemory;
}

void BlockMatrix::BlockMultiply(std::span<const double> a,
    std::span<const double> x,
    std::span<double> resultMemory) const {
    resultMemory[0] += a[0] * x[0];
    resultMemory[1] += a[0] * x[1];

    if (a.size() == 2) {
        resultMemory[0] -= a[1] * x[1];
        resultMemory[1] += a[1] * x[0];
    }
}

std::span<const double> BlockMatrix::GetBlockData(int i, int j) const {
    int currentBlockIndex;
    int length;

    if (i == j) {
        currentBlockIndex = _diagonalIndexes[i];
        length = GetDiagonalBlockSize(i);
        return std::span<const double>(_diagonal.data() + currentBlockIndex, length);
    }

    currentBlockIndex = _offDiagonalIndexes[j];
    length = GetOffDiagonalBlockSize(j);
    return std::span<const double>(_values.data() + currentBlockIndex, length);
}

int BlockMatrix::GetDiagonalBlockSize(int offset) const {
    return _diagonalIndexes[offset + 1] - _diagonalIndexes[offset];
}

int BlockMatrix::GetOffDiagonalBlockSize(int offset) const {
    return _offDiagonalIndexes[offset + 1] - _offDiagonalIndexes[offset];
}