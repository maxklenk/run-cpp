#include <iostream>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "ipc_player.h"
#include "shared_highscore.cpp"

using namespace boost::interprocess;

std::uint32_t readScore(std::uint32_t playerID) {
    std::cout << playerID << ": read " << std::endl;

    // Create a shared memory object.
    shared_memory_object shm(open_only, "MySharedMemory", read_write);

    // Map the whole shared memory in this process
    mapped_region region(shm, read_write);

    // Get the address of the mapped region
    void *addr = region.get_address();

    // Construct the shared structure in memory
    shared_highscore *data = static_cast<shared_highscore *>(addr);

    scoped_lock <interprocess_mutex> lock(data->mutex);

    std::uint32_t score = 0;
    const int PlayerLimit = 100;
    for (int i = 0; i < PlayerLimit; ++i) {
        if (data->highScore[i][0] == playerID) {
            score = data->highScore[i][1];
            break;
        }
        if (data->highScore[i][0] == 0) {
            break;
        }
    }

    return score;
}


void updateScore(std::uint32_t playerID, std::uint32_t newScore) {
    std::cout << playerID << ": update " << newScore << std::endl;

    // Create a shared memory object.
    shared_memory_object shm(open_only, "MySharedMemory", read_write);

    // Map the whole shared memory in this process
    mapped_region region(shm, read_write);

    // Get the address of the mapped region
    void *addr = region.get_address();

    // Construct the shared structure in memory
    shared_highscore *data = static_cast<shared_highscore *>(addr);

    scoped_lock <interprocess_mutex> lock(data->mutex);

    const int PlayerLimit = 100;
    for (int i = 0; i < PlayerLimit; ++i) {
        if (data->highScore[i][0] == playerID || data->highScore[i][0] == 0) {
            data->highScore[i][0] = playerID;
            data->highScore[i][1] = newScore;
            break;
        }
    }

    // Notify to the other process that there is an update
    data->cond_update.notify_one();

    // Mark as update available
    data->has_update = true;
}
