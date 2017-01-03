//
// Created by Tobias Wollowski on 02.01.17.
//

#ifndef GAME_H
#define GAME_H

#include "player.h"

class Game
{

private:
    std::vector<Player> players;
    friend std::ostream &operator<<(std::ostream &os, const Game &game);

public:
    Game(int players, int dices);

    void playRounds(unsigned int i);

    virtual int calculateScore(std::vector<int> rolls);

    ~Game();

};


///**
// * game for multiple players, each with 2 dices
// */
//class SevenCountsGame : Game
//{
//public:
//    SevenCountsGame(int players) : Game(players, 2) {};
//
//    int calculateScore(std::vector<int> rolls);
//};
//
///**
// * game for multiple players, each with 2 dices
// */
//class StuckInTheMudGame : Game
//{
//public:
//    StuckInTheMudGame(int players) : Game(players, 2) {};
//
//    int calculateScore(std::vector<int> rolls);
//};

#endif
