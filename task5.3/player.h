//
// Created by Tobias Wollowski on 02.01.17.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <vector>

#include "dice.h"

/* This is called a "forward declaration".  We use it to tell the compiler that the
   identifier "Game" will from now on stand for a class, and this class will be defined
   later.  We will not be able to make any use of "Game" before it has been defined, but
   we will at least be able to declare pointers to it. */
//class Game;

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