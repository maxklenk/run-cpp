#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "dice.h"

class Player
{
private:
    int player_num;
    std::vector<Dice> dices;
    int score;

    friend std::ostream &operator<<(std::ostream &os, const Player &player);

public:
    Player(int id, int dices);

    void updateScore(int points);

    std::vector<int> play();

};
