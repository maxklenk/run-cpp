#pragma once

#include <random>

class Dice
{
private:
    std::mt19937 seed;
    std::uniform_int_distribution<int> distribution {1,6};
public:
    Dice();
    int roll();
};
