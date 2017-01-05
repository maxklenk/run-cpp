#include <iostream>
#include <sstream>

#include "dice.h"
#include "player.h"
#include "game.h"


int main(int argc, char const * argv[])
{
    if(argc < 3){
        std::cout<< "set arguments: (1) the number of players and (2) the number of simulation rounds";
        return -1;
    }

    std::istringstream ssp(argv[1]);
    int num_players = 0;
    if (!(ssp >> num_players) || num_players < 1)
    {
        std::cerr << "Invalid player number " << argv[1] << '\n';
        return -2;
    }


    std::istringstream ssr(argv[2]);
    int num_sim_rounds = 0;
    if (!(ssr >> num_sim_rounds) || num_sim_rounds < 1)
    {
        std::cerr << "Invalid simulation rounds number " << argv[2] << '\n';
        return -3;
    }


    SevenCountsGame game(num_players);

    game.playRounds(num_sim_rounds);

    std::cout << game;

    return 0;
}