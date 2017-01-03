//
// Created by Tobias Wollowski on 02.01.17.
//

#ifndef DICE_H
#define DICE_H

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

#endif
