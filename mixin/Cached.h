
#pragma once

#include <utility>
#include <vector>

template<class Base>
class Cached : public Base {
public:
    explicit Cached(const std::pair<float, float> &center, float radius) : Base(center, radius) {
        this->resulution = 0;
        this->interpolation = false;
    }

    explicit Cached(const std::pair<float, float> &a, const std::pair<float, float> &b,
                    const std::pair<float, float> &c, const std::pair<float, float> &d) : Base(a, b, c, d) {
        this->resulution = 0;
        this->interpolation = false;
    };

    virtual ~Cached() = default;

    virtual void setCacheResolution(int res) {
        this->resulution = res;

        // set cache size
        this->cache = std::vector<std::pair<float, float>>(res);

        // fill cache
        float step = 1.0f / res;
        for (int i = 0; i < res; i++) {
            this->cache[i] = Base::operator()(i * step);
        }

    }

    void setUseLinearInterpolation(bool inter) {
        this->interpolation = inter;
    }

    virtual std::pair<float, float> operator()(float t) const {
        float step = 1.0f / this->resulution;
        if (this->interpolation) {
            float pos = t / step;
            int indexS = int(pos);
            int indexB = indexS + 1;

            double interpolation = 0.5; //pos - indexS;

            return std::pair<float, float>(
                    this->cache[indexS].first +
                    interpolation * (this->cache[indexB].first - this->cache[indexS].first),
                    this->cache[indexS].second +
                    interpolation * (this->cache[indexB].second - this->cache[indexS].second)
            );

        } else {
            int index = int(t / step + 0.5);
            return this->cache[index];
        }
    };

private:
    int resulution;
    bool interpolation;
    std::vector<std::pair<float, float>> cache;
};