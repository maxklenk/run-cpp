
#include <iostream>

#include "ipc_player.h"

std::uint32_t readScore(std::uint32_t playerID)
{
    std::cout << playerID << ": read " << std::endl;
	return 0;
}


void updateScore(std::uint32_t playerID, std::uint32_t newScore)
{
	std::cout << playerID << ": update " << newScore << std::endl;
}
