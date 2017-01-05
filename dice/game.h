#pragma once

#include "player.h"

/**
 * Abstract class for dice games of multiple players.
 * The calculateScore method should be overwritten in subclasses.
 */
class DiceGame
{

private:
    std::vector<Player> players;
    std::vector<Dice> dices;

    std::vector<int> play();

    friend std::ostream &operator<<(std::ostream &os, const DiceGame &game);

public:
    DiceGame(int players, int dices);

    void playRounds(int i);

    virtual int calculateScore(std::vector<int> rolls);

    ~DiceGame();

};


/**
 * “7 counts!” — A player always rolls the two dice at the same time.
 * If the sum of the dice is seven, then his or her score gets incremented.
 * Several players form a team. All team players can roll the dice a fixed number of times.
 * The winner is the person with the highest score.
 */
class SevenCountsGame : public DiceGame
{
public:
    SevenCountsGame(int players) : DiceGame(players, 2) {
        std::cout << " - mode: seven counts game..." << std::endl;};

    int calculateScore(std::vector<int> rolls);
};

/**
 * “Stuck-in-the-mud!” — A variant of the game uses five dices.
 * Players can only score on a roll which does not include the numbers 2 and 5.
 * Any dice, which show a 2 or a 5, become “Stuck in the mud!”.
 * If numbers 2 and 5 are not included, the total increments a player’s score.
 */
class StuckInTheMudGame : public DiceGame
{
public:
    StuckInTheMudGame(int players) : DiceGame(players, 2) {
        std::cout << " - mode: stuck in the mud game..." << std::endl;
    };

    int calculateScore(std::vector<int> rolls);
};
