In this demo, we are going to be playing with virtual member functions with polymorphic parameters.

# Painting the Picture

Let us say we have two abstract classes, Worker and Job. In other words, there are multiple kinds of Workers and multiple kinds of Jobs.

In this example, we will have just two different flavors of both Workers and Jobs. For Workers, we have WorkerA and WorkerB; for Jobs, we have ToughJob and EasyJob. Simple enough, right?

WorkerA is capable of doing ToughJobs and EasyJobs, but WorkerB is only capable of doing EasyJobs.

The Job struct is abstract, being inherited by ToughJob and EasyJob. Worker is also abstract, but the difference is that it has a virtual function, handleJob(Job).

# The Scenario

We have a WorkerA, a WorkerB, and a list of Jobs, both Tough and Easy.

