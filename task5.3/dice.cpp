//
// Created by Tobias Wollowski on 02.01.17.
//

#include "dice.h"

Dice::Dice(){
    std::random_device rd;
    this->seed = std::mt19937(rd());
}

int Dice::roll() {
    return distribution(this->seed);
}