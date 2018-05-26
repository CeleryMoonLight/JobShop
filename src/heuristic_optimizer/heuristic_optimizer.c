#include "heuristic_optimizer.h"

#include "../base.h"
#include "../ADT/ADT.h"

define_array(int);

extern p_order_t target_order;

typedef struct {
    int i;
    int j;
    int r;
    int q;
    int p;
} op_t;

p_operation_t ops;

bool *scheduled = NULL;
int *machine_schedule;
int *job_list;
void initialize_shifting_bottleneck_heuristic_optimizer() {
    ops = target_order->operations;
    scheduled = (bool *)calloc(target_order->num_of_machines, sizeof(bool));

}

void destroy_shifting_bottleneck_heuristic_optimizer() {
    free(scheduled);
    scheduled = NULL;
}

int longest_path(int m) {

}

int determain_bottleneck_machine() {
    int f = INT_MAX;
    int k = -1;
    for (size_t i = 0; i < target_order->num_of_machines; i++) {
        if (!scheduled[i]) {
            
        }
    }
}

void reschedule_scheduled_machines() {

}

void shifting_bottleneck_heuristic_optimize() {
    size_t scheduled_machine_count = 0;
    while (scheduled_machine_count < target_order->num_of_machines) {
        int m = determain_bottleneck_machine();
        scheduled[m] = true;
        scheduled_machine_count++;
        reschedule_scheduled_machines();
    }
}
