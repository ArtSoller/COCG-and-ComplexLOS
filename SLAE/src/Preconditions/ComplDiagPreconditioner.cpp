//#include "ComplDiagPreconditioner.h"
//
//ComplexDiagonalPreconditioner::ComplexDiagonalPreconditioner(const BlockMatrix& matrix)
//    : decomposed_matrix(
//        evaluate_inverse_diagonal(matrix)),  // diagonal
//        std::vector<double>(),                           // gg (empty)
//        matrix.get_diagonal_indexes(),                   // idi
//        std::vector<int>(),                              // ijg (empty)
//        std::vector<int>(matrix.size() + 1, 0),          // ig (zeros)
//        std::vector<int>()                               // jg (empty)
//    ) {
//}
//
//ComplexVector ComplexDiagonalPreconditioner::multiply_on(const ComplexVector& vector) const {
//    return decomposed_matrix.multiply_on(vector);
//}
//
//ComplexVector ComplexDiagonalPreconditioner::evaluate_inverse_diagonal(const BlockMatrix& matrix) {
//    int n = matrix.size();
//    std::vector<double> result(matrix.get_diagonal().size(), 0.0);
//    int offset = 0;
//
//    for (int i = 0; i < n; ++i) {
//        auto block = matrix.get_block(i, i);
//        int length = static_cast<int>(block.size());
//        double det = block[0] * block[0];
//
//        if (block.size() == 2) {
//            det += block[1] * block[1];
//            result[offset + 1] = -block[1] / det;
//        }
//
//        result[offset] = block[0] / det;
//        offset += length;
//    }
//
//    return ComplexVector::create(result);
//}