#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "dice.h"

/**
 * Player is identified by player_num and contains the current score which can be updated and fetched.
 */
class Player
{
private:
    int player_num;
    int score;

    friend std::ostream &operator<<(std::ostream &os, const Player &player);

public:
    Player(int player_num, int dices);

    void updateScore(int points);

    int getNum();
};
