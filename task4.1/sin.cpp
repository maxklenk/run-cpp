
#include <iostream>
#include <cmath>
#include <cstddef>
#include <utility>

constexpr auto pi = 3.1415926535897932384626433f;
constexpr auto pi_2 = 2 * pi;


constexpr float fastSinFill(const int i)
{
    // TODO optimize range to pi/2
    const float x = i / 1000.0f;
    const auto x_pow_3 = x * x * x;
    const auto x_pow_5 = x_pow_3 * x * x;
    return x - (x_pow_3 / 6) + (x_pow_5 / 120) - ((x_pow_5 * x * x) / 5040);
}


template<int N>
struct Table
{
    constexpr Table() : Table(std::make_index_sequence<N>{}) {}

    float values[N];
private:
    template<std::size_t... Is>
    constexpr Table(std::index_sequence<Is...>)
            : values{fastSinFill(Is) ...} {}
};

const size_t resolution = 1024;
constexpr auto sinTable = Table<3150>{};

/**
 * taylor series of degree seven for sine calculation.
 * max abs on ±pi is 0.0752206
 * @param x
 * @return
 */
float fastSin(float x)
{
    while (x > pi) x = (x - pi_2);
    while (x < -pi) x = (x + pi_2);
    if (x > 0)
        return sinTable.values[(int) (x * 1000.f)];
    else
        return -sinTable.values[(int) (x * -1000.f)];
}


int main(int argc, char const *argv[])
{

    float max_abs = 0.0f;

    for (size_t i = 0; i <= resolution; ++i)
    {
        auto value = i * 2.0f * pi / resolution;
        float actual = fastSin(value);
        float expected = std::sin(value);

        float abs = std::abs(actual - expected);
        max_abs = std::max(max_abs, abs);
        std::cout << i << ": " << value << " " << actual << "/" << expected << " -> " << abs
                  << std::endl;
    }
    std::cout << "max abs: " << max_abs;
}
