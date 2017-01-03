//
// Created by Tobias Wollowski on 02.01.17.
//

#include "game.h"

std::ostream &Game::operator<<(std::ostream &os)
{
    for (auto &player : this.getPlayers())
    {
        os << "player"; // TODO just out player
    }
    return os;
}

Game::Game(int players, int dices)
{
//    this->players = {};
    for (int i = 0; i < players; i++)
    {
        auto player = Player("player_" + i, dices, this);
        this->players.push_back(player);
    }
}

int SevenCountsGame::calculateScore(std::vector<int> rolls)
{
    int sum = 0;
    for (const auto &n : rolls)
        sum += n;
    if (sum == 7)
        return 1;
    return 0;
}

void Game::playRounds(unsigned int rounds)
{
    for (int i = 0; i < rounds; ++i)
    {
        for (auto &player : this->players)
        {
            player.play();
        }
    }
}

int StuckInTheMudGame::calculateScore(std::vector<int> rolls)
{
    int sum = 0;
    for (const auto &n :rolls)
    {
        if (n == 2 || n == 5)
        {
            return 0;
        }
        sum += n;
    }
    return sum;
}