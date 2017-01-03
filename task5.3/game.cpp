//
// Created by Tobias Wollowski on 02.01.17.
//

#include "player.h"
#include "game.h"

Game::Game(int players, int dices)
{
    std::cout << "create game..." << std::endl;
    this->players = std::vector<Player>();
    for (int i = 0; i < players; i++)
    {
        auto player = Player(i, dices);
        this->players.push_back(player);
    }
}

int Game::calculateScore(std::vector<int> rolls)
{
    std::cout << "return default result..." << std::endl;
    return 0;
};

Game::~Game()
{
    std::cout << "game destructed..." << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Game &game)
{
    for (auto &player : game.players)
    {
        os << player;
    }
    return os;
}

//int SevenCountsGame::calculateScore(std::vector<int> rolls)
//{
//    int sum = 0;
//    for (const auto &n : rolls)
//        sum += n;
//    if (sum == 7)
//        return 1;
//    return 0;
//}

void Game::playRounds(unsigned int rounds)
{
    for (int i = 0; i < rounds; ++i)
    {
        for (auto &player : this->players)
        {
            auto results = player.play();
            auto points = calculateScore(results);
            player.updateScore(points);
        }
    }
}

//int StuckInTheMudGame::calculateScore(std::vector<int> rolls)
//{
//    int sum = 0;
//    for (const auto &n :rolls)
//    {
//        if (n == 2 || n == 5)
//        {
//            return 0;
//        }
//        sum += n;
//    }
//    return sum;
//}
