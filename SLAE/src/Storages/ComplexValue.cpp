#include "ComplexValue.h"

ComplexValue::ComplexValue() : _size(1) {
    _values[0] = 0.0;
}

ComplexValue::ComplexValue(double real, double imaginary) {
    _values[0] = real;
    if (imaginary == 0.0) {
        _size = 1;
    }
    else {
        _values[1] = imaginary;
        _size = 2;
    }
}

double ComplexValue::Real() const {
    return _values[0];
}

double ComplexValue::Imaginary() const {
    return _size == 2 ? _values[1] : 0.0;
}