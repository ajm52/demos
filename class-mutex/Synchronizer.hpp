#ifndef SYNCHRONIZER_HPP
#define SYNCHRONIZER_HPP

#include <mutex>

class Synchronizer {
public:
    Synchronizer() : m(), data(0) {}
    inline std::mutex& getMutex() { return m; }
    inline int& getData() { return data; }
private:
    std::mutex m;
    int data;
};
#endif // SYNCHRONIZER_HPP