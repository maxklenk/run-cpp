// uniform_real_distribution
#include <iostream>
#include <random>
#include <math.h>

typedef double num_type;

int main(int argc, char *argv[]) {

    std::default_random_engine generator;
    std::uniform_real_distribution <num_type> distribution(0.0, 1.0);

    long inside = 0, outside = 0;
    double ratio;

    struct point2d {
        num_type x;
        num_type y;
    } point;

    int steps;
    while (steps != 10000) {

        num_type num = distribution(generator);
        std::cout << "num is " << num;

        if (std::sqrt(num * num) < 1) {
            inside++;
        } else {
            outside++;
        }

        ratio = double(inside + outside) / inside;
        std::cout << "ratio is " << ratio << std::endl;

        if (ratio > 3.1413 && ratio < 3.1419) {
            break;
        }
        steps++;
    }
    std::cout << "steps is " << steps << std::endl;
}



