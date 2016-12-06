
#include <iostream>

#include <boost/interprocess/managed_shared_memory.hpp>

#include "ipc_player.h"

using namespace boost::interprocess;

std::uint32_t readScore(std::uint32_t playerID)
{
    std::cout << playerID << ": read " << std::endl;
	return 0;
}


void updateScore(std::uint32_t playerID, std::uint32_t newScore)
{
	std::cout << playerID << ": update " << newScore << std::endl;

    return;
}
