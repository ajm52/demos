#include "WorkerThread.hpp"
#include "SharedObject.hpp"
#include <iostream>
#include <thread>
#include <mutex>

void workMethod(WorkerThread &wt)
{
    {
        std::lock_guard<std::mutex> lg(wt.so.m);
        std::cout << "T1 is about to modify SO..\n";
        wt.so.isReady = true;
        wt.so.cv.notify_one();
        std::cout << "T1 notified T2\n";
    }
}

void waitMethod(WorkerThread &wt)
{
    std::cout << "T2 is waiting for cond to change..\n";
    std::unique_lock<std::mutex> ul(wt.so.m);
    while (!wt.so.isReady)
    {
        wt.so.cv.wait(ul);
    }
    std::cout << "T2 has been notified.\n";
}

int main()
{
    SharedObject obj;
    WorkerThread wt1(obj);
    WorkerThread wt2(obj);
    std::thread t1(waitMethod, std::ref(wt1));
    std::thread t2(workMethod, std::ref(wt2));
    t1.join();
    t2.join();
    return 0;
}