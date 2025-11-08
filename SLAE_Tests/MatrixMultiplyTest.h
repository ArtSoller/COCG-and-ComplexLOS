//#pragma once
//
//#include "CppUnitTest.h"
//#include "../SLAE/src/Storages/BlockMatrix.h"
//#include "../SLAE/src/Storages/ComplexVector.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace SLAETests
//{
//    TEST_CLASS(MatrixMultiplyTest)
//    {
//    public:
//        TEST_METHOD(DefaultMultiplyOnVector1ShouldBeCorrect)
//        {
//            std::vector<double> di = { 1, 2, 3, 4, 5 };
//            std::vector<double> gg = { 1, 7, 8 };
//            std::vector<int> idi = { 0, 2, 4, 5 };
//            std::vector<int> ig = { 0, 0, 0, 2 };
//            std::vector<int> jg = { 0, 1 };
//            std::vector<int> ijg = { 0, 1, 3 };
//
//            auto matrix = BlockMatrix(di, gg, idi, ijg, ig, jg);
//            ComplexVector complexVector({ 1, 1, 1, 1, 1, 1 });
//
//            auto result = matrix.MultiplyOn(complexVector).GetValues();
//
//            ComplexVector expectedVector({ 0, 4, -2, 22, 5, 21 });
//            auto expected = expectedVector.GetValues();
//
//            for (size_t i = 0; i < expected.size(); ++i) {
//                Assert::AreEqual(expected[i], result[i]);
//            }
//        }
//
//        TEST_METHOD(DiagonalMatrixMultiplyOnVector1ShouldBeCorrect)
//        {
//            std::vector<double> di = { 1, 2, 3, 4, 5 };
//            std::vector<double> gg = {};
//            std::vector<int> idi = { 0, 2, 4, 5 };
//            std::vector<int> ig = { 0, 0, 0, 0 };
//            std::vector<int> jg = {};
//            std::vector<int> ijg = {};
//
//            auto matrix = BlockMatrix(di, gg, idi, ijg, ig, jg);
//            ComplexVector complexVector({ 1, 1, 1, 1, 1, 1 });
//
//            auto result = matrix.MultiplyOn(complexVector).GetValues();
//
//            ComplexVector expectedVector({ -1, 3, -1, 7, 5, 5 });
//            auto expected = expectedVector.GetValues();
//
//            for (size_t i = 0; i < expected.size(); ++i) {
//                Assert::AreEqual(expected[i], result[i]);
//            }
//        }
//    };
//}