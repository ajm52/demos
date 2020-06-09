#include "Synchronizer.hpp"
#include "Actor.hpp"
#include <iostream>
#include <chrono>

int main()
{
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
}