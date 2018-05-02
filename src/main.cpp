#include <iostream>
#include "jobshop.h"

int main(int argc, char *argv[]) {
    Scheduler *scheduler = new Scheduler();
    ConsoleReader *reader = new ConsoleReader();
    scheduler->Feed(/* Data */);
    GreedyOptimizer *optimizer = new GreedyOptimizer();
    scheduler->Run(optimizer);
    delete optimizer;
    delete reader;
    delete scheduler;
    return 0;
}
