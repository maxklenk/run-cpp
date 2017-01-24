
#pragma once

#include <utility>
#include <vector>
#include <cmath>
#include <iostream>


/** interface **/

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
    bool useLinearInterpolation = false;
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
//        std::cout << i << ": " << this->cache[i].first << ", " << this->cache[i].second << std::endl;
    }

}

template<class Base>
void Cached<Base>::setUseLinearInterpolation(bool interpolate)
{
    this->useLinearInterpolation = interpolate;
}

template<class Base>
std::pair<float, float> Cached<Base>::operator()(float t) const
{

    int resolution = this->cache.size();

    std::pair<float, float> result;

    if (this->useLinearInterpolation)
    {
        // calculate linear interpolation
        int before_idx = (int) (t * (resolution - 1));
        int next_idx = (int) std::min(before_idx + 1, resolution);

        if (before_idx == next_idx)
        {
            result = this->cache[before_idx];
        }
        else
        {

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
        }
    } else
    {
        // use nearest neighbour via rounding
        int index = (int) ((t * (resolution - 1)) + 0.5);
        result = this->cache[index];
    }
    return result;
};
