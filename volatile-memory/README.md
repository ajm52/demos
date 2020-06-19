# volatile-memory

In this demo, we are going to examine how member data can be written to and read from different threads, such that the data is consistent.

# experiment 1
We have 2 WorkerThreads and a SharedObject, which will have nothing but some primitive data. Thread #1 will continuously wait on a shared condition variable, breaking only when a particular data member of SharedObject reads true; this modification will be performed from Thread #2. Let's see what happens.