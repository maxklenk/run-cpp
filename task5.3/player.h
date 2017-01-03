//
// Created by Tobias Wollowski on 02.01.17.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <vector>

#include "dice.h"

class Player
{
private:
    int id;
    std::vector<Dice> dices;
    int score;

    friend std::ostream &operator<<(std::ostream &os, const Player &player);

public:
    Player(int id, int dices);

    void updateScore(int points);

    std::vector<int> play();

};

#endif