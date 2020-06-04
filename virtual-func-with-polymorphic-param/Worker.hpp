#ifndef WORKER_HPP
#define WORKER_HPP

#include <string>

// #include "EasyJob.hpp"
// #include "ToughJob.hpp"

struct EasyJob;
struct ToughJob;

class Worker
{
public:
    virtual void handleJob(EasyJob *) {}
    virtual void handleJob(ToughJob *) {}
};
#endif // WORKER_HPP