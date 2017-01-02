//
// Created by Tobias Wollowski on 02.01.17.
//

#ifndef DICE_PLAYER_H
#define DICE_PLAYER_H

#include <string>
#include <iostream>
#include <vector>
#include "dice.h"
#include "game.h"

class Player
{
private:
    std::string name;
    std::vector<Dice> dices;
    int score = 0;
    Game* game;
public:
    Player(std::string name, int dices, Game* game);

    void play();

    std::ostream& operator<< (std::ostream& os, Player& player);
};


#endif //DICE_PLAYER_H
