#include "MutexList.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <vector>

struct DummyFunc
{
    void operator()(unsigned id,
                    unsigned index,
                    MutexList &mList)
    {
        if (index >= mList.size_)
            return;
        std::cout << "T" << std::to_string(id) << " is trying to lock mutex "
                  << std::to_string(index) << std::endl;
        {
            std::lock_guard<std::mutex> lg(mList.data_.get()->at(index));
            std::cout << "T" << std::to_string(id) << " has locked mutex "
                      << std::to_string(index) << "; sleeping for 3s...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        std::cout << "T" << std::to_string(id) << " has unlocked mutex "
                  << std::to_string(index) << std::endl;
    }
};

int main()
{
    MutexList m1(5);
    MutexList m2(3);
    MutexList m3(std::move(m2));
    m3 = std::move(m1);

    if (!m2.data_)
        std::cout << "1" << std::endl;
    if (!m1.data_)
        std::cout << "1" << std::endl;
    std::cout << m3.validate() << std::endl;
    {
        std::lock_guard<std::mutex> lg((*m3.data_)[4]);
    }
    std::thread t1(DummyFunc(), 1, 4, std::ref(m3));
    std::thread t2(DummyFunc(), 2, 4, std::ref(m3));
    t1.join();
    t2.join();
    return 0;
}