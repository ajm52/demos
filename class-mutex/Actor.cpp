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
}