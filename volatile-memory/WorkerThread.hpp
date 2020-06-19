#ifndef WORKERTHREAD_HPP
#define WORKERTHREAD_HPP

#include "SharedObject.hpp"
#include <thread>

class WorkerThread
{
public:
    WorkerThread(SharedObject &obj) : so(obj) {}
    SharedObject &so;
};
#endif // WORKERTHREAD_HPP