#include <mutex>
#include <memory>
#include <vector>

struct MutexList
{
    MutexList(unsigned size) : data_(), size_(size) {}

    /**
     * builds the list of mutices.
     */
    void build();

    /**
     * checks size against the actual # of mutices;
     * validates that build() worked correctly.
     */
    bool validate();
    std::unique_ptr<std::vector<std::mutex>> data_;
    unsigned size_;
};
