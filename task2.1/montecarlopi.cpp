// uniform_real_distribution
#include <iostream>
#include <random>
#include <math.h>

/**
 * started coding by example from http://www.cplusplus.com/reference/random/uniform_real_distribution/
 */
int main(int argc, char *argv[])
{
    /*
    const int nrolls = 10000;  // number of experiments
    const int nstars = 95;     // maximum number of stars to distribute
    const int nintervals = 10; // number of intervals

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    int p[nintervals] = {};

    for (int i = 0; i < nrolls; ++i)
    {
        double number = distribution(generator);
        ++p[int(nintervals * number)];
    }

    std::cout << "uniform_real_distribution (0.0,1.0):" << std::endl;
    std::cout << std::fixed;
    std::cout.precision(1);

    for (int i = 0; i < nintervals; ++i)
    {
        std::cout << float(i) / nintervals << "-" << float(i + 1) / nintervals << ": ";
        std::cout << std::string(p[i] * nstars / nrolls, '*') << std::endl;
    }
    */

    const long size = 100000;

    std::vector<std::vector<bool> > matrix (size, std::vector<bool>(size));

    long values_inside = 0;

    for(long i = 0; i< size; i++)
    {
        for(long j = 0; j< size; j++)
        {
            if(sqrt(double(i)*double(i)+double(j)*double(j)) < size)
            {
                matrix[i][j] = true;
                values_inside++;
            }
        }
    }

/*
    // show what is 1 and inside the circle
    for(long i = 0; i<size; i++)
    {
        for(long j=0;j<size;j++)
        {
            if(matrix[i][j] == true)
            {
                std::cout << "1";
            }
            else
            {
                std::cout << "-";
            }
        }
        std::cout << std::endl;
    }        
    std::cout << std::endl;
    */

    double ratio = ( double(values_inside) / ( double(size) * double(size) ) ) * 4.0;

    std::cout << "Ratio: " << ratio << std::endl;

    return 0;
}
