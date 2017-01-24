
#pragma once

#include <utility>
#include <vector>

template<class Base>
class Cached : public Base
{
public:

    using Base::Base;

    virtual ~Cached() = default;

    void setCacheResolution(int res);

    void setUseLinearInterpolation(bool inter);

    virtual std::pair<float, float> operator()(float t) const;

private:
    bool interpolation;
    std::vector<std::pair<float, float>> cache;
};

/** implementation **/


template<class Base>
void Cached<Base>::setCacheResolution(int res)
{
    // set cache size
    this->cache = std::vector<std::pair<float, float>>(res);

    // fill cache
    for (int i = 0; i < res; ++i)
    {
        this->cache[i] = Base::operator()(float(i) / res);
    }

}

template<class Base>
void Cached<Base>::setUseLinearInterpolation(bool inter)
{
    this->interpolation = inter;
}

template<class Base>
std::pair<float, float> Cached<Base>::operator()(float t) const
{

    int resolution = this->cache.size();

    std::pair<float, float> result;

    if (this->interpolation)
    {
        // calculate linear interpolation
        int before_idx = int(t * (resolution-1));
        int next_idx = std::ceil(t * (resolution-1));

        if (before_idx == next_idx)
        {
            return this->cache[before_idx];
        }

        auto before_pt = this->cache[before_idx];
        auto next_pt = this->cache[next_idx];

        float x_interpol = ((t
                             - ((next_idx / resolution)
                                - (before_idx / resolution)))
                            * (next_pt.first - before_pt.first))
                           + before_pt.first;

        float y_interpol = before_pt.second
                           + ((x_interpol - before_pt.first)
                              * (next_pt.second - before_pt.second)
                              / (next_pt.first - before_pt.first));

        result = std::pair<float, float>(x_interpol, y_interpol);
    } else
    {
        // jump to rounded value
        int index = std::lround((t * (resolution-1)));
        result = this->cache[index];
    }
    return result;
};
