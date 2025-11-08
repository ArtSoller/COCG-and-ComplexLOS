#include "COCGSolver.h"
#include <stdexcept>

COCGSolver::COCGSolver(const ComplexDiagonalPreconditionerFactory& factory, const COCGConfig& config)
    : Method<COCGConfig>(config),
    _preconditionerFactory(factory),
    _preconditioner(BlockMatrix(std::vector<double>(), std::vector<double>(),
        std::vector<int>(), std::vector<int>(),
        std::vector<int>(), std::vector<int>())), // временная инициализация
    _equation(BlockMatrix(std::vector<double>(), std::vector<double>(),
        std::vector<int>(), std::vector<int>(),
        std::vector<int>(), std::vector<int>()),
        ComplexVector(), ComplexVector()), // временная инициализация
    _r(ComplexVector()),
    _z(ComplexVector()),
    _p(ComplexVector()),
    _rNext(ComplexVector()),
    _zNext(ComplexVector()),
    _pNext(ComplexVector())
{
}

ComplexVector COCGSolver::Solve(const ComplexEquation<BlockMatrix>& equation) {
    InitializeStartValues(equation);
    return IterationProcess();
}

void COCGSolver::InitializeStartValues(const ComplexEquation<BlockMatrix>& equation) {
    _preconditioner = _preconditionerFactory.CreatePreconditioner(equation.Matrix);
    _equation = equation;

    // _r = _equation.RightSide - _equation.Matrix.MultiplyOn(_equation.Solution);
    auto matrixTimesSolution = _equation.Matrix.MultiplyOn(_equation.Solution);
    _r = _equation.RightSide - matrixTimesSolution;

    // _z = _preconditioner.MultiplyOn(_r);
    _z = _preconditioner.MultiplyOn(_r);

    // _p = _z.Clone();
    _p = _z.Clone();
}

ComplexVector COCGSolver::IterationProcess() {
    auto solution = _equation.Solution;

    for (int i = 1; i < _config.MaxIterations; i++) {
        // Проверяем условие сходимости
        double residualNorm = _r.Norm();
        double rightSideNorm = _equation.RightSide.Norm();
        if (residualNorm / rightSideNorm <= _config.Epsilon) {
            break;
        }

        // a = _r.PseudoScalarProduct(_z) / _equation.Matrix.MultiplyOn(_p).PseudoScalarProduct(_p)
        auto numerator = _r.PseudoScalarProduct(_z);
        auto denominator = _equation.Matrix.MultiplyOn(_p).PseudoScalarProduct(_p);
        auto a = numerator / denominator;

        // solution += _p.MultiplyOn(a)
        solution = solution + _p.MultiplyOn(a);

        // _rNext = _r - _equation.Matrix.MultiplyOn(_p).MultiplyOn(a)
        auto matrixTimesP = _equation.Matrix.MultiplyOn(_p);
        _rNext = _r - matrixTimesP.MultiplyOn(a);

        // _zNext = _preconditioner.MultiplyOn(_rNext)
        _zNext = _preconditioner.MultiplyOn(_rNext);

        // b = _rNext.PseudoScalarProduct(_zNext) / _r.PseudoScalarProduct(_z)
        auto b_numerator = _rNext.PseudoScalarProduct(_zNext);
        auto b_denominator = _r.PseudoScalarProduct(_z);
        auto b = b_numerator / b_denominator;

        // _pNext = _zNext + _p.MultiplyOn(b)
        _pNext = _zNext + _p.MultiplyOn(b);

        // Обновляем векторы для следующей итерации
        _r = _rNext.Clone();
        _z = _zNext.Clone();
        _p = _pNext.Clone();
    }

    return solution;
}