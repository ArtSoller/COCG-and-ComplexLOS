//#pragma once
//#include "..//Storages/Method.h"
//#include "..//Storages/BlockMatrix.h"
//#include "..//Preconditions/ComplDiagPreconditioner.h"
//#include "..//Preconditions/ComplDiagPrecondFactory.h"
//#include <complex>
//
//struct ComplexEquation {
//    BlockMatrix Matrix;
//    ComplexVector Solution;
//    ComplexVector RightSide;
//
//    ComplexEquation(const BlockMatrix& matrix, const ComplexVector& solution, const ComplexVector& rightSide)
//        : Matrix(matrix), Solution(solution), RightSide(rightSide) {
//    }
//};
//
//struct COCGConfig {
//    int MaxIterations;
//    double Epsilon;
//
//    COCGConfig(int maxIterations, double epsilon)
//        : MaxIterations(maxIterations), Epsilon(epsilon) {
//    }
//};
//
//class COCGSolver : public Method<COCGConfig> {
//private:
//    ComplexDiagonalPreconditionerFactory _preconditionerFactory;
//    ComplexDiagonalPreconditioner _preconditioner;
//    ComplexEquation _equation;
//
//    ComplexVector _r;
//    ComplexVector _z;
//    ComplexVector _p;
//
//    ComplexVector _rNext;
//    ComplexVector _zNext;
//    ComplexVector _pNext;
//
//public:
//    explicit COCGSolver(const COCGConfig& config);
//
//    ComplexVector Solve(const ComplexEquation& equation);
//
//private:
//    void InitializeStartValues(const ComplexEquation& equation);
//    ComplexVector IterationProcess();
//};