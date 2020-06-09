#include "Listener.hpp"
#include "Actor.hpp"
#include <thread>
#include <mutex>
#include <iostream>

void Listener::init()
{
    std::thread t(&Listener::run, this);
    thread = std::move(t);
}

void Listener::run()
{
    int numDealtWith = 0;
    while (numDealtWith < cap)
    {
        std::unique_lock<std::mutex> ul(sq.getQueueMutexRef());
        while (true)
        {
            try
            {
                sq.getCvRef().wait(ul);
                if (ul.owns_lock())
                    break;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        std::cout << "Listener has locked sq.\n";
        while (!sq.getQueue().empty())
        {
            Actor *a = sq.getQueue().front();
            sq.getQueue().pop();
            actors.push_back(a);
            std::cout << "Listener dealing with " << a->id << std::endl;
            {
                std::lock_guard<std::mutex> lg(a->getMutexRef());
                a->flagService();
            }
            a->getCvRef().notify_one();
            std::cout << "Listener done with " << a->id << ", notified.\n";
            numDealtWith++;
        }
        ul.unlock();
        std::cout << "Listener has unlocked sq; numDealtWith=" << numDealtWith << "\n";
    }
    std::cout << "Listener done, exiting now.\n";
}