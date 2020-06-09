#include "Synchronizer.hpp"
#include "SafeQueue.hpp"
#include "Actor.hpp"
#include "Listener.hpp"
#include <iostream>
#include <chrono>

#define DEMO_2

int main()
{

#ifdef DEMO_1
    Synchronizer sync;
    Actor a1(sync), a2(sync), a3(sync);
    while (!a1.getThreadRef().joinable() || !a2.getThreadRef().joinable() || !a1.getThreadRef().joinable())
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    a1.getThreadRef().join();
    a2.getThreadRef().join();
    a3.getThreadRef().join();
    return 0;
#endif

#ifdef DEMO_2
    SafeQueue sq;
    Listener listener(sq, 3);
    Actor a1(sq, 1), a2(sq, 2), a3(sq, 3);
    while (!a1.getThreadRef().joinable() || !a2.getThreadRef().joinable() || !a1.getThreadRef().joinable() || !listener.getThreadRef().joinable())
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    a1.getThreadRef().join();
    a2.getThreadRef().join();
    a3.getThreadRef().join();
    listener.getThreadRef().join();
    return 0;
#endif
}