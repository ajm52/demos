in this demo, we look to answer the following question:

# C++ Boost API - Given a signal-slot connection, are slot callback functions fired asynchronously? (main.cpp)

That is, upon firing a signal that, in turn, triggers a given slot callback function, is the current thread of execution blocked until the callback function returns?

# RESULT 1

Upon compiling and executing the code in main.cpp, we can determine that the signal's thread of execution is indeed blocked until the slot callback function returns. We know this is the case, because the time registered before and after the signal call slightly over 2 seconds, which is exactly how long we have set the sleep duration within the callback function. 

# NEXT (main2.cpp)

Now that we have established this result, let us see if we can employ std::async to asynchronously launch the callback function, such that the signal's thread of execution is not blocked.

# RESULT 2

So. std::async requires that a Callable is passed in. I tried passing in the signal, but this did not work. That's when I thought: why not just define a Callable object and do away with signals and slots??? In other words, why not simply define a callback function (i.e. a "naked" slot) and pass that in to std::async? 

Turns out, this approach indeed gives us our desired result; the time duration before and after the "signal" is miniscule, and the duration before the signal and after the slot is over 2 seconds! In other words, the asynchronous function call is no longer blocking! We are only blocked when we call "get()" on the returned future object from the asynchronous function call, which is completely okay.

# CONCLUSION

Circling back to our original question: with normal usage, Boost's signal calling API does indeed seem to result in synchronous execution. That is, the thread of execution in which the signal is fired is blocked until the connected slot function returns. There may be some way to get around this by casting the Slot object to a Callable, but why go through all that trouble when one can just asynchronously trigger a callback function?