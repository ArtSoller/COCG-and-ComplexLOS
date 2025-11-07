#pragma once
#include <iostream>

template<typename TConfig>
class Method {
protected:
    TConfig _config;

public:
    explicit Method(const TConfig& config) : _config(config) {}
    virtual ~Method() = default;

protected:
    void Log(const std::string& message) const {
        std::cout << message << std::endl;
    }
};