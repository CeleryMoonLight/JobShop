/**
 * @brief Class Job
 * 
 * @file job.h
 * @author Jason Qiu
 * @date 2018-05-01
 */
#ifndef _JOB_H_
#define _JOB_H_

#include <vector>
#include "operation.h"

class Job {
public:
    Job();
    ~Job();
    void Add(const Operation &operation);
private:
    std::vector<Operation> jobs_;
};

#endif /* end of _JOB_H_ */
