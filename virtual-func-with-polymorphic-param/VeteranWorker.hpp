#ifndef VETERANWORKER_HPP
#define VETERANWORKER_HPP

#include "Worker.hpp"
#include "EasyJob.hpp"
#include "ToughJob.hpp"
#include <string>
#include <iostream>

class VeteranWorker : public Worker
{
public:
    void handleJob(ToughJob *tj)
    {
        std::cout << "this job is tough, but manageable for a vet.\n";
    }
    void handleJob(EasyJob *ej)
    {
        std::cout << "for a vet, this job is way too easy!\n";
    }
};
#endif // VETERANWORKER_HPP