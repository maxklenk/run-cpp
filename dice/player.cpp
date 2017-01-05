#include <string>
#include <iostream>

#include "dice.h"
#include "player.h"

Player::Player(int player_num, int dices)
{
    this->score = 0;
    this->player_num = player_num;
}

void Player::updateScore(int points)
{
    this->score += points;
}

int Player::getNum(){
    return this->player_num;
}

/**
 * scores printed to the console in the form “<player_num>: <score>\n”.
 * @param os
 * @param player
 * @return
 */
std::ostream &operator<<(std::ostream &os, const Player &player)
{
    os << "<" << player.player_num << ">: <" << player.score << ">\n";
    return os;
}