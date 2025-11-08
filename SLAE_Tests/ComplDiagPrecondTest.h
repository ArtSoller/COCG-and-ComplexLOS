//#pragma once
//#include "CppUnitTest.h"
//#include "../SLAE/src/Preconditions/ComplDiagPreconditioner.h"
//#include "../SLAE/src/Preconditions/ComplDiagPrecondFactory.h"
//#include "../SLAE/src/Storages/BlockMatrix.h"
//#include "../SLAE/src/Storages/ComplexVector.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace SLAETests
//{
//    TEST_CLASS(ComplexDiagonalPreconditionerTest)
//    {
//    private:
//        ComplexDiagonalPreconditioner* _preconditioner;
//
//    public:
//        TEST_METHOD_INITIALIZE(Setup)
//        {
//            std::vector<double> di = { 1, 2, 3, 5, 4 };
//            std::vector<double> gg = {};
//            std::vector<int> ig = { 0, 0, 0, 0 };
//            std::vector<int> jg = {};
//            std::vector<int> idi = { 0, 2, 3, 5 };
//            std::vector<int> ijg = {};
//
//            auto matrix = BlockMatrix(di, gg, idi, ijg, ig, jg);
//            auto factory = ComplexDiagonalPreconditionerFactory();
//            _preconditioner = new ComplexDiagonalPreconditioner(factory.CreatePreconditioner(matrix));
//        }
//
//        TEST_METHOD_CLEANUP(Cleanup)
//        {
//            delete _preconditioner;
//        }
//
//        TEST_METHOD(PreconditionerMultiplyOperationOnShouldBeCorrect)
//        {
//            ComplexVector vector({ 1, 2, 3, 4, 41, 82 });
//            auto result = _preconditioner->MultiplyOn(vector).GetValues();
//
//            std::vector<double> expected = { 1, 0, 1, 4.0 / 3.0, 13, 6 };
//
//            for (size_t i = 0; i < expected.size(); ++i) {
//                Assert::AreEqual(expected[i], result[i], 1e-10);
//            }
//        }
//    };
//}