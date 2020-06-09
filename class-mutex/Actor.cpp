#include "Actor.hpp"
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

void Actor::init()
{
    std::thread t(&Actor::run, this);
    thread = std::move(t);
}

void Actor::run()
{
#ifdef DEMO_1
    while (true)
    {
        std::cout << std::this_thread::get_id() << " is attempting to lock mutex.\n";
        {
            std::lock_guard<std::mutex> lg(sync.getMutex());
            std::cout << std::this_thread::get_id() << " has locked mutex.\n";
            int &data = sync.getData();
            std::cout << "sync data reads " << std::to_string(data) << std::endl;
            if (data == 10)
            {
                std::cout << "work is done, time to go! breaking loop, unlocking mutex.\n";
                break;
            }
            else
            {
                data += 1;
                std::cout << "after incr, sync data now reads " << std::to_string(sync.getData()) << std::endl;
            }
            std::cout << "unlocking...\n";
        }
        std::cout << std::this_thread::get_id() << " has unlocked the mutex; sleeping for 3 seconds...\n\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
#endif
#ifdef DEMO_2
    std::cout << "Thread " << id << " is attempting to lock mutex.\n";
    {
        std::lock_guard<std::mutex> lg(safequeue.getQueueMutexRef());
        std::cout << "Thread " << id << " has locked mutex.\n";
        safequeue.getQueue().push(this);
        std::cout << "Thread " << id << " has entered SafeQueue.\n";
    }

    safequeue.getCvRef().notify_one();
    std::cout << "Thread " << id << " has notified Listener; waiting to hear back.\n";
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    std::unique_lock<std::mutex> ul(m);
    cv.wait(ul, [this] { return hasBeenServiced(); });
    std::cout << "Thread " << id << " has been serviced! Bye for now.\n";
#endif
}