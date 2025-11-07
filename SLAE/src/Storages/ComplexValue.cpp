#include "ComplexValue.h"

ComplexValue::ComplexValue() : _values{ 0.0 }, _hasImaginary(false) {}

ComplexValue::ComplexValue(double real, double imaginary)
    : _values{ real, imaginary }, _hasImaginary(imaginary != 0.0) {
}

ComplexValue ComplexValue::Create(double real, double imaginary) {
    return ComplexValue(real, imaginary);
}

double ComplexValue::Real() const {
    return _values[0];
}

double ComplexValue::Imaginary() const {
    return _hasImaginary ? _values[1] : 0.0;
}

bool ComplexValue::HasImaginary() const {
    return _hasImaginary;
}