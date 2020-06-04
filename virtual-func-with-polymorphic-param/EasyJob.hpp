#ifndef EASYJOB_HPP
#define EASYJOB_HPP

#include "Job.hpp"
#include "Worker.hpp"
#include <string>

struct EasyJob : public Job
{
    void accept(Worker &w) { w.handleJob(this); }
};
#endif // EASYJOB_HPP