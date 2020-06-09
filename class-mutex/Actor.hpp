#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "Synchronizer.hpp"
#include <thread>

class Actor
{
public:
    Actor(Synchronizer &s) : sync(s) { init(); }
    void init();
    void run();
    inline std::thread &getThreadRef() { return thread; }

private:
    Synchronizer &sync;
    std::thread thread;
};
#endif // ACTOR_HPP