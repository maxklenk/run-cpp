//
// Created by Tobias Wollowski on 02.01.17.
//

#include <string>
#include <iostream>
#include "dice.h"
#include "player.h"

Player::Player(std::string name, int dices, Game *game)
{
    this->name = name;
    for (int i = 0; i < dices; i++)
    {
        this->dices.push_back(Dice());
    }
    this->game = game;
}

void Player::play()
{
    std::vector<int> results;
    for (int i = 0; i < this->dices.size(); i++)
    {
        results.push_back(this->dices[i].roll());
    }
    auto currentScore = this->game->calculateScore(results);

    this->score+=currentScore;
}

std::ostream &Player::operator<<(std::ostream &os, Player &player)
{
    os << name << ": " << score << "\n";
    return os;
}