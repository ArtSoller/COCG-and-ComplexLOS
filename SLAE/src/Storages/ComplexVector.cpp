#include "ComplexVector.h"
#include <cmath>
#include <stdexcept>

ComplexVector::ComplexVector() : _values() {}

ComplexVector::ComplexVector(const std::vector<double>& values) : _values(values) {}

ComplexVector::ComplexVector(int length) : _values(length, 0.0) {}

const std::vector<double>& ComplexVector::GetValues() const {
    return _values;
}

int ComplexVector::Length() const {
    return static_cast<int>(_values.size());
}

double ComplexVector::Norm() const {
    return std::sqrt(ScalarProductInternal(*this, *this).real());
}

ComplexVector ComplexVector::Clone() const {
    return ComplexVector(_values);
}

ComplexVector ComplexVector::operator+(const ComplexVector& other) const {
    if (Length() != other.Length()) {
        throw std::invalid_argument("Vectors must have the same length");
    }

    std::vector<double> result(Length());
    for (int i = 0; i < Length(); i++) {
        result[i] = _values[i] + other._values[i];
    }

    return ComplexVector(result);
}

ComplexVector ComplexVector::operator-(const ComplexVector& other) const {
    if (Length() != other.Length()) {
        throw std::invalid_argument("Vectors must have the same length");
    }

    std::vector<double> result(Length());
    for (int i = 0; i < Length(); i++) {
        result[i] = _values[i] - other._values[i];
    }

    return ComplexVector(result);
}

ComplexVector& ComplexVector::operator+=(const ComplexVector& other) {
    if (Length() != other.Length()) {
        throw std::invalid_argument("Vectors must have the same length");
    }

    for (int i = 0; i < Length(); i++) {
        _values[i] += other._values[i];
    }

    return *this;
}

ComplexVector& ComplexVector::operator-=(const ComplexVector& other) {
    if (Length() != other.Length()) {
        throw std::invalid_argument("Vectors must have the same length");
    }

    for (int i = 0; i < Length(); i++) {
        _values[i] -= other._values[i];
    }

    return *this;
}

ComplexVector ComplexVector::MultiplyOn(const std::complex<double>& complexScalar) const {
    auto resultMemory = Clone();

    for (int i = 0; i < Length() / 2; i++) {
        std::complex<double> z(_values[i * 2], _values[i * 2 + 1]);
        auto aByZ = complexScalar * z;

        resultMemory._values[i * 2] = aByZ.real();
        resultMemory._values[i * 2 + 1] = aByZ.imag();
    }

    return resultMemory;
}

std::complex<double> ComplexVector::ScalarProduct(const ComplexVector& outerVector) const {
    return ScalarProductInternal(*this, outerVector);
}

std::complex<double> ComplexVector::PseudoScalarProduct(const ComplexVector& outerVector) const {
    return PseudoScalarProductInternal(*this, outerVector);
}

std::complex<double> ComplexVector::ScalarProductInternal(const ComplexVector& a, const ComplexVector& b) {
    if (a.Length() % 2 != 0 || b.Length() % 2 != 0) {
        throw std::invalid_argument("Vectors must have an even length");
    }

    if (a.Length() != b.Length()) {
        throw std::invalid_argument("Vector and result must have same length");
    }

    std::complex<double> sum = 0;
    for (int i = 0; i < a.Length() / 2; ++i) {
        std::complex<double> aComplex(a._values[2 * i], -a._values[2 * i + 1]);
        std::complex<double> bComplex(b._values[2 * i], b._values[2 * i + 1]);

        sum += aComplex * bComplex;
    }

    return sum;
}

std::complex<double> ComplexVector::PseudoScalarProductInternal(const ComplexVector& a, const ComplexVector& b) {
    if (a.Length() % 2 != 0 || b.Length() % 2 != 0) {
        throw std::invalid_argument("Vectors must have an even length");
    }

    if (a.Length() != b.Length()) {
        throw std::invalid_argument("Vector and result must have same length");
    }

    std::complex<double> sum = 0;
    for (int i = 0; i < a.Length() / 2; ++i) {
        std::complex<double> aComplex(a._values[2 * i], a._values[2 * i + 1]);
        std::complex<double> bComplex(b._values[2 * i], b._values[2 * i + 1]);

        sum += aComplex * bComplex;
    }

    return sum;
}