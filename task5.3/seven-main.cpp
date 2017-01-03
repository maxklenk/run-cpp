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
    unsigned int num_players;
    if (!(ssp >> num_players))
        std::cerr << "Invalid player number " << argv[1] << '\n';


    std::istringstream ssr(argv[1]);
    unsigned int num_sim_rounds;
    if (!(ssr >> num_sim_rounds))
        std::cerr << "Invalid simulation rounds number " << argv[1] << '\n';


    Game game(num_players,2);

    std::cout << game;

    game.playRounds(num_sim_rounds);

    std::cout << game;

    return 0;
}