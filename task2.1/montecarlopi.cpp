// uniform_real_distribution
#include <iostream>
#include <random>
#include <math.h>
#include <typeinfo>

typedef double num_type;
//typedef long double num_type;
//typedef float num_type;

int main(int argc, char *argv[]) {

    std::default_random_engine generator;
    std::uniform_real_distribution <num_type> distribution(0.0, 1.0);

    long inside = 0;
    long outside = 0;
    num_type ratio;

    struct Point2d {

        num_type x;
        num_type y;

        num_type dist() {
            return std::sqrt((x * x) + (y * y));
        }

    };

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



