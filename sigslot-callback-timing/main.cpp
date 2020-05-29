#include <boost/signals2.hpp>
#include <future>
#include <thread>
#include <chrono>
#include <iostream>

struct DemoSlot
{
    std::chrono::system_clock::time_point operator()()
    {
        auto beforeSleep = std::chrono::high_resolution_clock::now(); // timestamp BEFORE the callback simulated computation.
        std::this_thread::sleep_for(std::chrono::seconds(2));         // simulating computation ...
        return beforeSleep;
    }
};

int main()
{
    std::cout << "beginning sigslot-callback-timing demo ...\n";
    boost::signals2::signal<std::chrono::system_clock::time_point()> sig;
    DemoSlot slot;
    sig.connect(slot);
    auto beforeSig = std::chrono::high_resolution_clock::now(); // timestamp BEFORE the signal
    auto beforeSlot = sig().get();
    auto afterSig = std::chrono::high_resolution_clock::now(); // timestamp AFTER the callback trigger
    std::chrono::duration<double, std::milli> d1 = beforeSlot - beforeSig, d2 = afterSig - beforeSig;
    std::cout << "\n\ntime between BeforeSig and BeforeSlot: " << d1.count() << " ms.\n";
    std::cout << "time between BeforeSig and AfterSig: " << d2.count() << " ms.\n";
    return 0;
}