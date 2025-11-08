#include "pch.h"
#include "CppUnitTest.h"

// ¬ключаем все тестовые заголовки
#include "ComplexValueTest.h"
#include "ComplDiagPrecondTest.h" 
#include "MatrixMultiplyTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SLAETests
{
    // Ётот класс остаетс€ пустым - все тесты в отдельных заголовках
    TEST_CLASS(SLAETests)
    {
    public:
        TEST_METHOD(PlaceholderTest)
        {
            Assert::IsTrue(true);
        }
    };
}