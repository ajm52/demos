#include <mutex>
#include <memory>
#include <vector>

struct MutexList
{
    MutexList(unsigned size = 0)
        : size_(size),
          data_(new std::vector<std::mutex>(size_)) {}

    MutexList(MutexList &&);
    MutexList &operator=(MutexList &&);

    /**
     * builds the list of mutices.
     */
    void build();

    /**
     * checks size against the actual # of mutices;
     * validates that build() worked correctly.
     */
    bool validate();
    unsigned size_;
    std::unique_ptr<std::vector<std::mutex>> data_;
};
