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

    void playRounds(int i);

    virtual int calculateScore(std::vector<int> rolls);

    ~Game();

};


/**
 * game for multiple players, each with 2 dices
 */
class SevenCountsGame : public Game
{
public:
    SevenCountsGame(int players) : Game(players, 2) {
        std::cout << " - mode: seven counts game..." << std::endl;};

    int calculateScore(std::vector<int> rolls);
};

/**
 * game for multiple players, each with 2 dices
 */
class StuckInTheMudGame : public Game
{
public:
    StuckInTheMudGame(int players) : Game(players, 2) {
        std::cout << " - mode: stuck in the mud game..." << std::endl;
    };

    int calculateScore(std::vector<int> rolls);
};

#endif
