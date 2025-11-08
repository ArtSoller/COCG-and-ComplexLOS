#pragma once

class ComplexValue {
private:
    double _values[2];
    int _size;

public:
    ComplexValue();
    ComplexValue(double real, double imaginary = 0.0);

    double Real() const;
    double Imaginary() const;
};
