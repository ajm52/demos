in this demo, we look to answer the following question:

# (C++ Boost API) Given a signal-slot connection, are slot callback functions fired asynchronously?

That is, upon firing a signal that, in turn, triggers a given slot callback function, is the current thread of execution blocked until the callback function returns?