#pragma once
#include <vector>
#include <complex>
#include <cmath>
#include <stdexcept>

class ComplexVector {
private:
    std::vector<double> _values;

public:
    ComplexVector() = default;

    explicit ComplexVector(const std::vector<double>& values);
    explicit ComplexVector(int length);

    const std::vector<double>& GetValues() const;
    int Length() const;
    double Norm() const;

    ComplexVector Clone() const;

    ComplexVector operator+(const ComplexVector& other) const;
    ComplexVector operator-(const ComplexVector& other) const;

    ComplexVector MultiplyOn(const std::complex<double>& complexScalar) const;

    std::complex<double> ScalarProduct(const ComplexVector& outerVector) const;
    std::complex<double> PseudoScalarProduct(const ComplexVector& outerVector) const;

private:
    static std::complex<double> ScalarProduct(const ComplexVector& a, const ComplexVector& b);
    static std::complex<double> PseudoScalarProduct(const ComplexVector& a, const ComplexVector& b);
};