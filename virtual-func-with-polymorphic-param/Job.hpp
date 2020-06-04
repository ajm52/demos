#ifndef JOB_HPP
#define JOB_HPP

#include "Worker.hpp"

struct Job
{
    virtual void accept(Worker &) = 0;
};
#endif // JOB_HPP