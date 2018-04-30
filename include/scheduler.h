#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "optimizer.h"

class Scheduler {
public:
    Scheduler();
    explicit Scheduler(IOptimizer *optimizer);
    ~Scheduler();
    void Feed();
    void Run();
private:
    Scheduler(const Scheduler &);
    Scheduler &operator=(const Scheduler &);
};

#endif /* end of _SCHEDULER_H_ */
