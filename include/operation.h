/**
 * @brief Class Operation
 * 
 * @file operation.h
 * @author Jason Qiu
 * @date 2018-05-01
 */
#ifndef _OPERATION_H_
#define _OPERATION_H_

class Job;

class Operation {
public:
    Operation(int period, int machine);
    ~Operation();
    int period_;
    int machine_;
    Job *job_ = nullptr;
};

#endif /* end of _OPERATION_H_ */
