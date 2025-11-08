#include "ComplexVector.h"
#include <stdexcept>
#include <cmath>

ComplexVector::ComplexVector(int length) : _values(length, 0.0) {}

ComplexVector::ComplexVector(const std::vector<double>& values) : _values(values) {}

const std::vector<double>& ComplexVector::GetValues() const {
    return _values;
}

int ComplexVector::Length() const {
    return _values.size();
}

double ComplexVector::Norm() const {
    return std::sqrt(ScalarProduct(*this, *this).real());
}

ComplexVector ComplexVector::Clone() const {
    return ComplexVector(*this);
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

ComplexVector ComplexVector::MultiplyOn(const std::complex<double>& complexScalar) const {
    if (Length() % 2 != 0) {
        throw std::invalid_argument("Vector must have even length");
    }

    std::vector<double> result(Length());

    for (int i = 0; i < Length() / 2; i++) {
        std::complex<double> z(_values[i * 2], _values[i * 2 + 1]);
        std::complex<double> aByZ = complexScalar * z;

        result[i * 2] = aByZ.real();
        result[i * 2 + 1] = aByZ.imag();
    }

    return ComplexVector(result);
}

std::complex<double> ComplexVector::ScalarProduct(const ComplexVector& outerVector) const {
    return ScalarProduct(*this, outerVector);
}

std::complex<double> ComplexVector::PseudoScalarProduct(const ComplexVector& outerVector) const {
    return PseudoScalarProduct(*this, outerVector);
}

std::complex<double> ComplexVector::ScalarProduct(const ComplexVector& a, const ComplexVector& b) {
    if (a.Length() % 2 != 0 || b.Length() % 2 != 0) {
        throw std::invalid_argument("Vectors must have an even length");
    }

    if (a.Length() != b.Length()) {
        throw std::invalid_argument("Vectors must have same length");
    }

    std::complex<double> sum(0.0, 0.0);
    for (int i = 0; i < a.Length() / 2; ++i) {
        std::complex<double> aComplex(a._values[2 * i], -a._values[2 * i + 1]);
        std::complex<double> bComplex(b._values[2 * i], b._values[2 * i + 1]);

        sum += aComplex * bComplex;
    }

    return sum;
}

std::complex<double> ComplexVector::PseudoScalarProduct(const ComplexVector& a, const ComplexVector& b) {
    if (a.Length() % 2 != 0 || b.Length() % 2 != 0) {
        throw std::invalid_argument("Vectors must have an even length");
    }

    if (a.Length() != b.Length()) {
        throw std::invalid_argument("Vectors must have same length");
    }

    std::complex<double> sum(0.0, 0.0);
    for (int i = 0; i < a.Length() / 2; ++i) {
        std::complex<double> aComplex(a._values[2 * i], a._values[2 * i + 1]);
        std::complex<double> bComplex(b._values[2 * i], b._values[2 * i + 1]);

        sum += aComplex * bComplex;
    }

    return sum;
}