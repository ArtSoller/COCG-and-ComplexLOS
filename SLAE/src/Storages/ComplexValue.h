#pragma once

class ComplexValue {
private:
    double _values[2];
    bool _hasImaginary;

public:
    ComplexValue();
    ComplexValue(double real, double imaginary = 0.0);

    static ComplexValue Create(double real, double imaginary);

    double Real() const;
    double Imaginary() const;
    bool HasImaginary() const;
};