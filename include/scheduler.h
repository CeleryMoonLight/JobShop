/**
 * @brief Class Scheduler
 * 
 * @file scheduler.h
 * @author Jason Qiu
 * @date 2018-05-01
 */
#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "optimizer.h"

class Scheduler {
public:
    Scheduler();
    /**
     * @brief Construct a new Scheduler object
     * 
     * @param optimizer 
     */
    explicit Scheduler(IOptimizer *optimizer);
    ~Scheduler();
    void Feed();
    void Run();
private:
    Scheduler(const Scheduler &);
    Scheduler &operator=(const Scheduler &);
};

#endif /* end of _SCHEDULER_H_ */
