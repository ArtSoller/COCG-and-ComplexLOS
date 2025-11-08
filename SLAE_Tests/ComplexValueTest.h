//#pragma once
//
//#include "CppUnitTest.h"
//#include "../SLAE/src/Storages/ComplexValue.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace SLAETests
//{
//    TEST_CLASS(ComplexValueTest)
//    {
//    public:
//        TEST_METHOD(RealValueShouldBeCorrect)
//        {
//            auto complexValue = ComplexValue(1.0, 0.0);
//
//            auto realValue = complexValue.Real();
//            auto imaginaryValue = complexValue.Imaginary();
//
//            const double expectedReal = 1;
//            const double expectedImaginary = 0;
//
//            Assert::AreEqual(expectedReal, realValue);
//            Assert::AreEqual(expectedImaginary, imaginaryValue);
//        }
//
//        TEST_METHOD(ImaginaryValueShouldBeCorrect)
//        {
//            auto complexValue = ComplexValue(0.0, 15.0);
//
//            auto realValue = complexValue.Real();
//            auto imaginaryValue = complexValue.Imaginary();
//
//            const double expectedReal = 0;
//            const double expectedImaginary = 15;
//
//            Assert::AreEqual(expectedReal, realValue);
//            Assert::AreEqual(expectedImaginary, imaginaryValue);
//        }
//
//        TEST_METHOD(ComplexValueShouldBeCorrect)
//        {
//            auto complexValue = ComplexValue(151.0, 15.0);
//
//            auto realValue = complexValue.Real();
//            auto imaginaryValue = complexValue.Imaginary();
//
//            const double expectedReal = 151;
//            const double expectedImaginary = 15;
//
//            Assert::AreEqual(expectedReal, realValue);
//            Assert::AreEqual(expectedImaginary, imaginaryValue);
//        }
//
//        TEST_METHOD(EmptyConstructorValueShouldBeCorrect)
//        {
//            auto complexValue = ComplexValue();
//
//            auto realValue = complexValue.Real();
//            auto imaginaryValue = complexValue.Imaginary();
//
//            const double expectedReal = 0;
//            const double expectedImaginary = 0;
//
//            Assert::AreEqual(expectedReal, realValue);
//            Assert::AreEqual(expectedImaginary, imaginaryValue);
//        }
//    };
//}