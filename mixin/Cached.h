
#pragma once

#include <utility>

template <class Base>
class Cached: public Base
{
public:
    explicit Cached(const std::pair<float, float> & center, float radius) : Base(center, radius)  {};
    explicit Cached(const std::pair<float, float> & a, const std::pair<float, float> & b, const std::pair<float, float> & c, const std::pair<float, float> & d) : Base(a, b, c, d) {};
    virtual ~Cached() = default;

    virtual void setCacheResolution(int res) {
        this->resulution = res;
    }
    void setUseLinearInterpolation(bool inter) {
        this->interpolation = inter;
    }

    virtual std::pair<float, float> operator()(float t) const {
        return Base::operator()(t);
    };

private:
    int resulution;
    bool interpolation;
};