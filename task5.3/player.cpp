#include <string>
#include <iostream>

#include "dice.h"
#include "player.h"

Player::Player(int id, int dices)
{
    this->score = 0;
    this->player_num = id;
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
    std::cout << "  - player_" << this->player_num << ": ";
    for (auto &result: results)
        std::cout << result << " ";
    std::cout << std::endl;
    return results;
}


std::ostream &operator<<(std::ostream &os, const Player &player)
{
    os << "<" << player.player_num << ">: <" << player.score << ">\n";
    return os;
}