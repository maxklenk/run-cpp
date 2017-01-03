//
// Created by Tobias Wollowski on 02.01.17.
//

#include <string>
#include <iostream>

#include "dice.h"
#include "player.h"

Player::Player(int id, int dices)
{
    this->score = 0;
    this->id = id;
    for (int i = 0; i < dices; i++)
    {
        this->dices.push_back(Dice());
    }
}

void Player::updateScore(int points)
{
    this->score += points;
}

std::vector<int> Player::play()
{
    std::vector<int> results;
    for (int i = 0; i < this->dices.size(); i++)
    {
        results.push_back(this->dices[i].roll());
    }
//    auto currentScore = this->game->calculateScore(results);
//
//    this->score += currentScore;
    return results;
}


std::ostream &operator<<(std::ostream &os, const Player &player)
{
    os << "player_" << player.id << ": " << player.score << "\n";
    return os;
}