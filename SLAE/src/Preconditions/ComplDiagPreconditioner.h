//#pragma once
//#include "../Storages/BlockMatrix.h"
//#include "../Storages/ComplexVector.h"
//
//class ComplexDiagonalPreconditioner {
//private:
//    BlockMatrix decomposed_matrix;
//
//public:
//    explicit ComplexDiagonalPreconditioner(const BlockMatrix& matrix);
//
//    ComplexVector multiply_on(const ComplexVector& vector) const;
//
//private:
//    static ComplexVector evaluate_inverse_diagonal(const BlockMatrix& matrix);
//};