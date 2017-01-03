//
// Created by Tobias Wollowski on 02.01.17.
//

#include "player.h"

class Game
{
    friend std::ostream &operator<<(std::ostream &os, const Game &game);

private:
    std::vector<Player> players;

public:
    Game(int players, int dices);

    void playRounds(unsigned int i);

    virtual int calculateScore(std::vector<int> rolls);

    virtual ~Game();
};

std::ostream &operator<<(std::ostream &os, const Game &game)
{
    for (auto &player : game.players)
    {
        os << player;
    }
    return os;
}

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
