#include "MutexList.hpp"

void MutexList::build()
{
    if (data_->size() > 0 || data_->size() < size_)
        data_.reset(new std::vector<std::mutex>(size_));
}

bool MutexList::validate()
{
    return data_->size() == size_;
}