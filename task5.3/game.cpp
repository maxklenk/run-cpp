//
// Created by Tobias Wollowski on 02.01.17.
//

#include "player.h"
#include "game.h"

DiceGame::DiceGame(int players, int dices)
{
    std::cout << "create default game... " << players << " players, " << dices << " dices" << std::endl;
    this->players = std::vector<Player>();

    for (int i = 0; i < players; )
    {
        auto player = Player(++i, dices);
        this->players.push_back(player);
    }
}

int DiceGame::calculateScore(std::vector<int> rolls)
{
    std::cout << "calculate default score..." << std::endl;
    return 0;
};

DiceGame::~DiceGame()
{
    std::cout << "default game destructed..." << std::endl;
}

std::ostream &operator<<(std::ostream &os, const DiceGame &game)
{
    for (auto &player : game.players)
    {
        os << player;
    }
    return os;
}

int SevenCountsGame::calculateScore(std::vector<int> rolls)
{
    int sum = 0, result = 0;
    for (const auto &n : rolls)
        sum += n;
    if (sum == 7)
        result = 1;

    std::cout << "    seven counts score (sum is " << sum << "): " << result << std::endl;
    return result;
}

void DiceGame::playRounds(int rounds)
{
    std::cout << " - play rounds: " << rounds << std::endl;
    for (int i = 0; i < rounds; )
    {
        std::cout << "- round: " << ++i << std::endl;
        for (auto &player : this->players)
        {
            auto results = player.play();
            auto points = calculateScore(results);
            player.updateScore(points);
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
            sum = 0;
            break;
        }
        sum += n;
    }
    std::cout << "    stuck in the mud score: " << sum << std::endl;
    return sum;
}
