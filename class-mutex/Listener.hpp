#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "SafeQueue.hpp"
#include <thread>
#include <vector>
#include <condition_variable>

class Actor;

class Listener
{
public:
    Listener(SafeQueue &safequeue, int numToDealWith) : sq(safequeue), cap(numToDealWith) { init(); }
    void init();
    void run();
    inline std::thread &getThreadRef() { return thread; }
    inline bool workToBeDone() { return !sq.getQueue().empty(); }

private:
    std::thread thread;
    SafeQueue &sq;
    std::vector<Actor *> actors;
    int cap;
};
#endif // LISTENER_HPP