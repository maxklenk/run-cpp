//
// Created by Tobias Wollowski on 02.01.17.
//

#ifndef GAME_H
#define GAME_H

#include "player.h"

class DiceGame
{

private:
    std::vector<Player> players;
    friend std::ostream &operator<<(std::ostream &os, const DiceGame &game);

public:
    DiceGame(int players, int dices);

    void playRounds(int i);

    virtual int calculateScore(std::vector<int> rolls);

    ~DiceGame();

};


/**
 * game for multiple players, each with 2 dices
 */
class SevenCountsGame : public DiceGame
{
public:
    SevenCountsGame(int players) : DiceGame(players, 2) {
        std::cout << " - mode: seven counts game..." << std::endl;};

    int calculateScore(std::vector<int> rolls);
};

/**
 * game for multiple players, each with 2 dices
 */
class StuckInTheMudGame : public DiceGame
{
public:
    StuckInTheMudGame(int players) : DiceGame(players, 2) {
        std::cout << " - mode: stuck in the mud game..." << std::endl;
    };

    int calculateScore(std::vector<int> rolls);
};

#endif
