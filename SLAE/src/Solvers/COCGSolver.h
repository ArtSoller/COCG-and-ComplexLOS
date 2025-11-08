#pragma once
#include "../Storages/Method.h"
#include "../Preconditions/ComplDiagPrecondFactory.h"
#include "../Storages/BlockMatrix.h"
#include "../Storages/ComplexVector.h"
#include <memory>

struct COCGConfig {
    int MaxIterations;
    double Epsilon;

    COCGConfig(int maxIterations, double epsilon)
        : MaxIterations(maxIterations), Epsilon(epsilon) {
    }
};

template<typename TMatrix>
struct ComplexEquation {
    TMatrix Matrix;
    ComplexVector Solution;
    ComplexVector RightSide;

    ComplexEquation() = default;

    ComplexEquation(const TMatrix& matrix, const ComplexVector& solution, const ComplexVector& rightSide)
        : Matrix(matrix), Solution(solution), RightSide(rightSide) {
    }
};

class COCGSolver : public Method<COCGConfig> {
private:
    ComplexDiagonalPreconditionerFactory _preconditionerFactory;
    ComplexDiagonalPreconditioner _preconditioner;
    ComplexEquation<BlockMatrix> _equation;

    ComplexVector _r;
    ComplexVector _z;
    ComplexVector _p;

    ComplexVector _rNext;
    ComplexVector _zNext;
    ComplexVector _pNext;

public:
    COCGSolver(const ComplexDiagonalPreconditionerFactory& factory, const COCGConfig& config);

    ComplexVector Solve(const ComplexEquation<BlockMatrix>& equation);

private:
    void InitializeStartValues(const ComplexEquation<BlockMatrix>& equation);
    ComplexVector IterationProcess();
};