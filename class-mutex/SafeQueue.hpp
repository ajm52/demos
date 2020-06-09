#ifndef SAFEQUEUE_HPP
#define SAFEQUEUE_HPP

#include <queue>
#include <condition_variable>
#include <mutex>

class Actor;

class SafeQueue
{
public:
    SafeQueue() : queueM(), cv(), q() {}
    inline std::queue<Actor *> &getQueue() { return q; }
    inline std::condition_variable &getCvRef() { return cv; }
    inline std::mutex &getQueueMutexRef() { return queueM; }

private:
    std::mutex queueM;
    std::condition_variable cv;
    std::queue<Actor *> q;
};
#endif // SAFEQUEUE_HPP