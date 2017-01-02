//
// Created by Tobias Wollowski on 02.01.17.
//

#ifndef DICE_GAME_H
#define DICE_GAME_H


#include "player.h"

class Game
{
protected:
    std::vector<Player> players;

    Game(int players, int dices);

public:
    virtual int calculateScore(std::vector<int> rolls) { return 0; };

    std::ostream &operator<<(std::ostream &os, Game &game);

    std::vector<Player> getPlayers() { return players; };

    virtual void playRounds(unsigned int i);
};

/**
 * game for multiple players, each with 2 dices
 */
class SevenCountsGame : Game
{
public:
    SevenCountsGame(int players) : Game(players, 2) {};

    int calculateScore(std::vector<int> rolls);
};

/**
 * game for multiple players, each with 2 dices
 */
class StuckInTheMudGame : Game
{
public:
    StuckInTheMudGame(int players) : Game(players, 2) {};

    int calculateScore(std::vector<int> rolls);
};


#endif //DICE_GAME_H
