#ifndef SHAREDOBJECT_HPP
#define SHAREDOBJECT_HPP

#include <mutex>
#include <condition_variable>

struct SharedObject
{
    SharedObject() : isReady(false), cv(), m() {}
    bool isReady;
    std::condition_variable cv;
    std::mutex m;
};
#endif // SHAREDOBJECT_HPP