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

    struct Point2d {

        num_type x;
        num_type y;

        num_type dist() {
            return std::sqrt((x * x) + (y * y));
        }

    };

    int steps;
    while (steps != 10000) {

        Point2d point {distribution(generator), distribution(generator)};

        std::cout << "point is x: " << point.x << " y:" << point.y << std::endl;
        std::cout << "dist is " << point.dist() << " less 1? " << (point.dist() < 1.0 ? " true" : " false") << std::endl;

        if (point.dist() < 1.0) {
            inside++;
        } else {
            outside++;
        }

        ratio =  4.0 * double(inside) / ( double(inside) + double(outside) );
        std::cout << "inside: " << inside << " outside: " << outside << " ratio is " << ratio << std::endl;

        if (ratio > 3.1413 && ratio < 3.1419) {
            std::cout << "PI sucks! ";
            break;
        }
        steps++;
    }
    std::cout << "steps: " << steps << std::endl;
}



