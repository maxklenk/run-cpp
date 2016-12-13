#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "ipc_viewer.h"
#include "shared_highscore.cpp"

using namespace boost::interprocess;

std::map <std::uint32_t, std::uint32_t> readHighScore(bool block) {
    auto myMap = std::map<std::uint32_t, std::uint32_t>();

    // Run the remover once if you want to clean up the shared Memory
//    struct shm_remove
//    {
//        shm_remove() { shared_memory_object::remove("MySharedMemory"); }
//        ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
//    } remover;

    // Access Shared Object
    shared_memory_object shm(open_or_create, "MySharedMemory", read_write);

    // Set size
    shm.truncate(sizeof(shared_highscore));

    // Map the whole shared memory in this process
    mapped_region region(shm, read_write);

    // Get the address of the mapped region
    void *addr = region.get_address();

    // Obtain a pointer to the shared structure
    shared_highscore *data = new(addr) shared_highscore;

    // Lock Access
    scoped_lock <interprocess_mutex> lock(data->mutex);

    if (!data->has_update && block) {
        data->cond_update.wait(lock);
    }

    for (auto score : data->highScore) {
        if (score[0] != 0) {
            myMap.insert(std::make_pair(score[0], score[1]));
        } else {
            break;
        }
    }

    // Mark that we read everything
    data->has_update = false;

    return myMap;
}

