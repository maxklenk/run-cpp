#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

struct shared_highscore {
    enum {
        PlayerLimit = 100
    };

    shared_highscore() : has_update(false) {}

    // Mutex to protect access to the score
    boost::interprocess::interprocess_mutex mutex;

    // Condition to wait when the score has no update
    boost::interprocess::interprocess_condition cond_update;

    // Score to save
    int highScore[PlayerLimit][2];

    // Is there a new update
    bool has_update;
};