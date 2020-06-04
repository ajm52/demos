#include "NewbieWorker.hpp"
#include "VeteranWorker.hpp"
#include "ToughJob.hpp"
#include "EasyJob.hpp"
#include "Job.hpp"
#include "Worker.hpp"
#include <iostream>

int main()
{
    Worker &vw = *(new VeteranWorker);
    Worker &nw = *(new NewbieWorker);
    Job &j1 = *(new ToughJob);
    Job &j2 = *(new EasyJob);
    j1.accept(vw);
    j1.accept(nw);
    j2.accept(nw);
    j2.accept(vw);
}