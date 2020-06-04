#include "MutexList.hpp"

MutexList::MutexList(MutexList &&ml)
    : size_(ml.size_),
      data_(ml.data_.release())
{
}

MutexList &MutexList::operator=(MutexList &&ml)
{
    if (this == &ml)
        return *this;

    size_ = ml.size_;
    data_.reset(ml.data_.release());
    return *this;
}

void MutexList::build()
{
    if (data_->size() > 0 || data_->size() < size_)
        data_.reset(new std::vector<std::mutex>(size_));
}

bool MutexList::validate()
{
    return data_->size() == size_;
}