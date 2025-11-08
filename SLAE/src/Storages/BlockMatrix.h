#pragma once
#include "ComplexVector.h"
#include <vector>
#include <span>
#include <stdexcept>

class BlockMatrix {
public:
    std::vector<int> _diagonalIndexes;
    std::vector<int> _rowIndex;
    std::vector<int> _offDiagonalIndexes;
    std::vector<int> _columnIndex;
    std::vector<double> _diagonal;
    std::vector<double> _values;

    BlockMatrix(const std::vector<double>& di,
        const std::vector<double>& gg,
        const std::vector<int>& idi,
        const std::vector<int>& ijg,
        const std::vector<int>& ig,
        const std::vector<int>& jg);

    int Size() const;
    std::span<const double> operator()(int i, int j) const;

    ComplexVector MultiplyOn(const ComplexVector& vector, ComplexVector* resultMemory = nullptr) const;
    BlockMatrix Clone() const;

private:
    ComplexVector BlockMatrixMultiply(const ComplexVector& vector, ComplexVector& resultMemory) const;
    void BlockMultiply(std::span<const double> a, std::span<const double> x, std::span<double> resultMemory) const;
    std::span<const double> GetBlockData(int i, int j) const;
    int GetDiagonalBlockSize(int offset) const;
    int GetOffDiagonalBlockSize(int offset) const;
};
