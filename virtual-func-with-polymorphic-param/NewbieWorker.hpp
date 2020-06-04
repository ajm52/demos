#ifndef NEWBIEWORKER_HPP
#define NEWBIEWORKER_HPP

#include "Worker.hpp"
#include "ToughJob.hpp"
#include "EasyJob.hpp"
#include <iostream>

class NewbieWorker : public Worker
{
public:
    void handleJob(ToughJob *tj)
    {
        std::cout << "this job is too tough for a newbie.\n";
    }
    void handleJob(EasyJob *ej)
    {
        std::cout << "for a newbie, this job is manageable...\n";
    }
};
#endif // NEWBIEWORKER_HPP