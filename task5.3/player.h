//
// Created by Tobias Wollowski on 02.01.17.
//

#include <string>
#include <iostream>
#include <vector>
#include "dice.h"

/* This is called a "forward declaration".  We use it to tell the compiler that the
   identifier "Game" will from now on stand for a class, and this class will be defined
   later.  We will not be able to make any use of "Game" before it has been defined, but
   we will at least be able to declare pointers to it. */
class Game;

class Player
{
    friend std::ostream &operator<<(std::ostream &os, const Player &player);

private:
    std::string name;
    std::vector<Dice> dices;
    int score;
    Game *game;
public:
    Player(std::string name, int dices, Game *game);

    void play();

};

std::ostream &operator<<(std::ostream &os, const Player &player)
{
    os << player.name << ": " << player.score << "\n";
    return os;
}
