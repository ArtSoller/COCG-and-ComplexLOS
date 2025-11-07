#pragma once
#include <vector>
#include "ComplexVector.h"

class BlockMatrix {
private:
    std::vector<int> _diagonalIndexes;
    std::vector<int> _rowIndex;
    std::vector<int> _offDiagonalIndexes;
    std::vector<int> _columnIndex;
    std::vector<double> _diagonal;
    std::vector<double> _values;

public:
    BlockMatrix(
        const std::vector<double>& di,
        const std::vector<double>& gg,
        const std::vector<int>& idi,
        const std::vector<int>& ijg,
        const std::vector<int>& ig,
        const std::vector<int>& jg
    );

    int Size() const;
    std::vector<double> GetBlock(int i, int j) const;

    ComplexVector MultiplyOn(const ComplexVector& vector) const;
    BlockMatrix Clone() const;

private:
    void BlockMultiply(const std::vector<double>& a, const std::vector<double>& x, std::vector<double>& resultMemory, int resultOffset) const;
    std::vector<double> GetBlockData(int i, int j) const;
    int GetDiagonalBlockSize(int offset) const;
    int GetOffDiagonalBlockSize(int offset) const;
};