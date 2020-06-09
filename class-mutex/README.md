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

SafeQueue is the intermediary data structure, accessible by Actors and the Listener. Actors take turns "entering" SafeQueue, while Listener "waits" to be notified of their entry. Upon being notified, Listener removes all Actors in the SafeQueue, notifying them after doing so. All of these actions are done with thread safety kept at the forefront:

- Actors must lock SafeQueue's mutex before "entering"
- Listener must "wait" to be notified before looking at SafeQueue
- Listener must lock an Actor's mutex before changing the service flag and notifying

# result 2

Success! It works. Though there were multiple subtleties that threw me off here and there, the biggest one was dealing with Listener's wait/lock.

From what I can tell, constructing a <unique_lock> with a <mutex> reference will lock the mutex as soon as it is available to do so. Thus, all I did was write a wait() loop to guard against spurious wakeups; owning the lock would permit Listener to break the loop. We place the wait() call inside a try/catch, just in case we happen to encounter some sort of exception.

Other worthy mentions:

- when creating threads within respective init() methods, be sure to move the thread to a member variable, so it can be joined from another thread of execution (i.e. main()).
- when working with thread-related class member data (i.e. condvars, mutices), always implement getters to return by reference. Returning a pointer can result in unwarranted behavior.
