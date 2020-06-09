# mutex, as a class member.

In today's demo, we're going to investigate the usage of <mutex> as a data member of a class. As thread safety is a rather tricky topic, things get even trickier when threads and mutices are data members. How does one achieve thread-safe synchronized access between multiple threads of class member data?

# demo 1

We have two main objects, Synchronizer and Actor. The former has two data members, a mutex and an int. 3 thread-based Actors are created in main(), which increment Synchronizer's data until 10 is reached, at which point they all exit. 

# result 1

Well there we go, that wasn't too hard. 

I would say the trickiest part about this demo was dealing with the Actor thread, such that it would be joinable from main(). We achieve this by creating a local thread in init() and moving it into a member variable, so it can then be accessed by reference from main().

One thing I noticed was that calling detach() from inside Actor::init() made the thread permanently unjoinable.

# demo 2

Now, we are going to make the thread actions slightly more interesting, throwing in a locally accessible data structure, some condition variables, and another thread-based class.

Listener will "wait" to be notified, at which point it will look in its queue, pull all Actors out, place them in the next location, and notify back. This should be a little more interesting.

