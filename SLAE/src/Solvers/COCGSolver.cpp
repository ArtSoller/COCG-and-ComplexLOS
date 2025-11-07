//#include "COCGSolver.h"
//#include <cmath>
//#include <stdexcept>
//
//COCGSolver::COCGSolver(const COCGConfig& config)
//    : Method<COCGConfig>(config), _preconditionerFactory() {}
//
//ComplexVector COCGSolver::Solve(const ComplexEquation& equation) {
//    InitializeStartValues(equation);
//    return IterationProcess();
//}
//
//void COCGSolver::InitializeStartValues(const ComplexEquation& equation) {
//    _preconditioner = _preconditionerFactory.CreatePreconditioner(equation.Matrix);
//    _equation = equation;
//
//    _r = _equation.RightSide - _equation.Matrix.MultiplyOn(_equation.Solution);
//    _z = _preconditioner.MultiplyOn(_r);
//    _p = _z.Clone();
//}
//
//ComplexVector COCGSolver::IterationProcess() {
//    auto solution = _equation.Solution;
//
//    for (int i = 1; i < _config.MaxIterations && _r.Norm() / _equation.RightSide.Norm() > _config.Epsilon; i++) {
//        auto ap = _equation.Matrix.MultiplyOn(_p);
//        auto numerator = _r.PseudoScalarProduct(_z);
//        auto denominator = ap.PseudoScalarProduct(_p);
//
//        if (std::abs(denominator) < 1e-15) {
//            throw std::runtime_error("Division by zero in COCG solver");
//        }
//
//        std::complex<double> a = numerator / denominator;
//        solution = solution + _p.MultiplyOn(a);
//
//        _rNext = _r - ap.MultiplyOn(a);
//        _zNext = _preconditioner.MultiplyOn(_rNext);
//
//        auto b = _rNext.PseudoScalarProduct(_zNext) / _r.PseudoScalarProduct(_z);
//        _pNext = _zNext + _p.MultiplyOn(b);
//
//        _r = _rNext.Clone();
//        _z = _zNext.Clone();
//        _p = _pNext.Clone();
//    }
//
//    return solution;
//}