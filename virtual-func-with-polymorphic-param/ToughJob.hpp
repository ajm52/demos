#ifndef TOUGHJOB_HPP
#define TOUGHJOB_HPP

#include "Job.hpp"
#include "Worker.hpp"

struct ToughJob : public Job
{
    void accept(Worker &w) { w.handleJob(this); }
};
#endif // TOUGHJOB_HPP