
#include <iostream>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "ipc_player.h"

using namespace boost::interprocess;

std::uint32_t readScore(std::uint32_t playerID) {
    std::cout << playerID << ": read " << std::endl;

    shared_memory_object shm{open_or_create, "HighScore", read_write};
    shm.truncate(1024);

    // Map the whole shared memory in this process
    mapped_region region(shm, read_only);

    // Check that memory
    std::uint32_t *i1 = static_cast<std::uint32_t *>(region.get_address());
    i1++;

    return *i1;
}


void updateScore(std::uint32_t playerID, std::uint32_t newScore) {
    std::cout << playerID << ": update " << newScore << std::endl;

    shared_memory_object shm{open_or_create, "HighScore", read_write};
    shm.truncate(1024);

    // Map the whole shared memory in this process
    mapped_region region(shm, read_write);

    int *i1 = static_cast<int *>(region.get_address());
    *i1 = playerID;
    i1++;
    *i1 = newScore;

    return;
}
