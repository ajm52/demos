#include <future>
#include <thread>
#include <chrono>
#include <iostream>

struct DemoCallback
{
    int operator()()
    {
        std::this_thread::sleep_for(std::chrono::seconds(2)); // simulating computation ...
        return 1;
    }
};

int main()
{
    std::cout << "beginning sigslot-callback-timing demo ...\n";
    auto beforeSig = std::chrono::high_resolution_clock::now(); // timestamp BEFORE the signal
    std::future<int> beforeCallback = std::async(std::launch::async, DemoCallback());
    auto afterSig = std::chrono::high_resolution_clock::now(); // timestamp AFTER the callback trigger
    int retVal = beforeCallback.get();                         // this will block until we have a value to return from DemoCallback().
    auto afterSlot = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> d1 = afterSlot - beforeSig, d2 = afterSig - beforeSig;
    std::cout << "\n\ntime between BeforeSig and AfterSlot: " << d1.count() << " ms.\n";
    std::cout << "time between BeforeSig and AfterSig: " << d2.count() << " ms.\n";
    return 0;
}