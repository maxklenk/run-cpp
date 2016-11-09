// uniform_real_distribution
#include <iostream>
#include <random>
#include <math.h>
#include <typeinfo>
#include <chrono>

// define current number type
typedef float num_type;
//typedef double num_type;
//typedef long double num_type;

// change random number generation
//#define RANDOM_NUMBERS 1;

int main(int argc, char *argv[]) {

#ifdef RANDOM_NUMBERS
    // time dependent random value (will result in changing values)
    std::mt19937_64 generator;
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    generator.seed(ss);
    std::cout << "use time dependend random" << std::endl;
#else
    // default random (will result in fixed numbers)
    std::default_random_engine generator;
    std::cout << "use default random engine" << std::endl;
#endif

    std::uniform_real_distribution <num_type> distribution(0.0, 1.0);

    struct Point2d {

        num_type x;
        num_type y;

        num_type dist() {
            return std::sqrt((x * x) + (y * y));
        }

    };

    int inside = 0;
    int outside = 0;
    num_type ratio;

    int steps = 0;
    int inRange = 0;
    while (inRange != 10000) {

        Point2d point{distribution(generator), distribution(generator)};

        if (point.dist() < 1.0) {
            inside++;
        } else {
            outside++;
        }

        ratio = num_type(4) * inside / (inside + outside);

        if (ratio > num_type(3.1413) && ratio < num_type(3.1419)) {
            inRange++;
        } else {
            inRange = 0;
        }

        steps++;
    }

    std::cout.precision(128);
    std::cout << "steps: " << steps << std::endl;
    std::cout << "PI: " << ratio << " " << typeid(ratio).name() << " " << sizeof(ratio) << std::endl;
}



