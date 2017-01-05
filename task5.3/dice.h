#pragma once

#include <random>

/**
 * Generates (pseudo-) random numbers in range 1...6.
 * The generated numbers are (pseudo-) independent for each Dice instance.
 */
class Dice
{
private:
    std::mt19937 seed;
    std::uniform_int_distribution<int> distribution {1,6};
public:
    Dice();
    int roll();
};
