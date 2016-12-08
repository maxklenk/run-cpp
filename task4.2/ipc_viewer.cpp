
#include <iostream>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "ipc_viewer.h"

using namespace boost::interprocess;

std::map <std::uint32_t, std::uint32_t> readHighScore(bool block) {
    std::cout << "read " << block << std::endl;

    auto myMap = std::map<std::uint32_t, std::uint32_t>();

    shared_memory_object shm{open_or_create, "HighScore", read_write};
    shm.truncate(1024);

    // Map the whole shared memory in this process
    mapped_region region(shm, read_only);

    // Check that memory
    int *i2 = static_cast<int *>(region.get_address());
    std::uint32_t playerId = *i2;
    i2++;
    std::uint32_t score = *i2;

    myMap.insert(std::make_pair(playerId, score));

    return myMap;
}

