#ifndef ACTOR_HPP
#define ACTOR_HPP

#define DEMO_2

#include "Synchronizer.hpp"
#include "SafeQueue.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>

class Actor
{
public:
#ifdef DEMO_1
    Actor(Synchronizer &s) : sync(s), cv(), m(), serviceFlag(false)
    {
        init();
    }
#endif

#ifdef DEMO_2
    Actor(SafeQueue &sq, unsigned num) : safequeue(sq), cv(), m(), serviceFlag(false), id(num)
    {
        init();
    }
#endif
    void init();
    void run();
    inline std::thread &getThreadRef() { return thread; }
    inline std::condition_variable &getCvRef() { return cv; }
    inline std::mutex &getMutexRef() { return m; }
    inline bool hasBeenServiced() { return serviceFlag; }
    inline void flagService() { serviceFlag = true; }
    unsigned id;

private:
#ifdef DEMO_1
    Synchronizer &sync;
#endif

#ifdef DEMO_2
    SafeQueue &safequeue;
#endif
    std::thread thread;
    std::condition_variable cv;
    std::mutex m;
    bool serviceFlag;
};
#endif // ACTOR_HPP