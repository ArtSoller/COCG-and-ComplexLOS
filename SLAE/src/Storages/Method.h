#pragma once
#include <memory>

template<typename TConfig>
class Method {
protected:
    TConfig _config;

public:
    Method(const TConfig& config) : _config(config) {}

    virtual ~Method() = default;

    Method(const Method&) = delete;
    Method& operator=(const Method&) = delete;

protected:
    const TConfig& GetConfig() const { return _config; }
};