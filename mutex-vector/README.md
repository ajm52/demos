# demo3

this one is simple enough: In the context of c++11, how does one go about emulating a list of mutices (plural of mutex)?

while the question is simple, the nature of the mutex makes the answer rather evasive. Based off of this thread [here](https://stackoverflow.com/questions/16465633/how-can-i-use-something-like-stdvectorstdmutex), we shall see what we can do.

# result 1

as with anything, there's always more than one way to skin a cat. One way to achieve this would be to have a unique_ptr of a C array of mutices, but given that std::vector is more robust and user-friendly, I went with std::unique_ptr<std::vector<std::mutex> >. 

All the work for this one is done in the initializer list. Simpler than I thought it would be.

# part 2 : concurrent access

Now, we are going to play around with some threads. As you can imagine, concurrent access to a unique_ptr of objects does not make much sense. We will see how this goes first, then we shall make a second MutexList object that operates with shared_ptr.

# result 2

So, we have achieved the results we wanted; concurrent access to a list of mutices. In doing so, I found a rather pedantic subtlety to do with unique_ptrs. While I thought that the essence of unique_ptrs was that its resource (i.e. vector<mutex>) may only be accessed by one thread at a time, it ACTUALLY means that only ONE unique_ptr may point to a given resource, whereas OTOH, multiple shared_ptrs may point to a given resource. 

This would likely be obvious to a CPP vet, but as I am still quite the noob, this was an interesting find.