#include "job.h"

Job::Job() {

}

Job::~Job() {

}

void Job::Add(const Operation &operation)
{
    jobs_.push_back(operation);
    jobs_.back().job_ = this;
}
