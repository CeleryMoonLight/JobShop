/**
 * @brief Implementation of heuristic_optimizer.h.
 * 
 * @file heuristic_optimizer.c
 * @author Jason Qiu
 * @date 2018-05-26
 */
#include "heuristic_optimizer/heuristic_optimizer.h"

#include "base.h"

#include "ADT/ADT.h"

typedef struct {
    int machine;  //  Machine
    int job;  //  Job
    int r;  //  head
    int q;  //  Tail
    int p;  //  Period
    int in_degree;
    bool in_u;
    p_operation_t operation;
} node_t;

typedef node_t *p_node_t;

define_queue(p_node_t);
define_array(int);

extern p_order_t target_order;

bool *scheduled = NULL;
p_array_t(int) *machine_schedule = NULL;
p_node_t *machine_node_list = NULL;

p_queue_t(p_node_t) zero_degree = NULL;

void initialize_shifting_bottleneck_heuristic_optimizer() {
    scheduled = (bool *)calloc(target_order->num_of_machines, sizeof(bool));
    machine_schedule = (p_array_t(int) *)calloc(target_order->num_of_machines, sizeof(p_array_t(int)));
    for (size_t index = 0; index < target_order->num_of_machines; index++) {
        machine_schedule[index] = new_array(int, target_order->num_of_jobs);
    }
    machine_node_list = (p_node_t *)calloc(target_order->num_of_machines, sizeof(p_node_t));
    for (size_t index = 0; index < target_order->num_of_machines; index++) {
        machine_node_list[index] = (p_node_t)calloc(target_order->num_of_jobs, sizeof(node_t));
    }
    for (size_t i = 0; i < target_order->num_of_jobs; i++) {
        for (size_t j = 0; j < target_order->operations_of_jobs[i]; j++) {
            machine_node_list[target_order->operations[i][j].machine][i].machine = target_order->operations[i][j].machine;
            machine_node_list[target_order->operations[i][j].machine][i].job = target_order->operations[i][j].job;
            machine_node_list[target_order->operations[i][j].machine][i].p = target_order->operations[i][j].period;
            machine_node_list[target_order->operations[i][j].machine][i].operation = &(target_order->operations[i][j]);
            push_back(machine_schedule[target_order->operations[i][j].machine], target_order->operations[i][j].job);
        }
    }
    zero_degree = new_queue(p_node_t, target_order->num_of_operations);
}

void destroy_shifting_bottleneck_heuristic_optimizer() {
    assert(scheduled != NULL);
    free(scheduled);
    scheduled = NULL;
    assert(machine_schedule != NULL);
    for (int index = 0; index < target_order->num_of_machines; index++) {
        delete_array(machine_schedule[index]);
    }
    free(machine_schedule);
    machine_schedule = NULL;
}
#include <stdio.h>
int longest_path() {
    // Calculate r_i
    // 初始化入度
    for (size_t index = 0; index < target_order->num_of_machines; index++) {
        for (size_t node_index = 0; node_index < size(machine_schedule[index]); node_index++) {
            if (machine_node_list[index][machine_schedule[index]->data[node_index]].operation != NULL) {
                machine_node_list[index][machine_schedule[index]->data[node_index]].in_degree = 1;
                if (scheduled[index]) {
                    machine_node_list[index][machine_schedule[index]->data[node_index]].in_degree += node_index;
                }
                if (machine_node_list[index][machine_schedule[index]->data[node_index]].operation->index == 0) {
                    machine_node_list[index][machine_schedule[index]->data[node_index]].in_degree--;
                }
                if (machine_node_list[index][machine_schedule[index]->data[node_index]].in_degree == 0) {
                    machine_node_list[index][machine_schedule[index]->data[node_index]].r = 0;
                    push(zero_degree, &machine_node_list[index][machine_schedule[index]->data[node_index]]);
                } else {
                    machine_node_list[index][machine_schedule[index]->data[node_index]].r = INT_MAX;
                }
            }
        }
    }
    while (!is_empty(zero_degree)) {
        
        p_node_t node = front(zero_degree);
        pop(zero_degree);
        // update release time
        int max_length = node->operation->index == 0 ? 0 
        : machine_node_list[target_order->operations[node->job][node->operation->index - 1].machine]
                            [target_order->operations[node->job][node->operation->index - 1].job].r
                            + target_order->operations[node->job][node->operation->index - 1].period;
        if (node->operation->index != target_order->operations_of_jobs[node->job] - 1) {
            machine_node_list[target_order->operations[node->job][node->operation->index + 1].machine]
                [target_order->operations[node->job][node->operation->index + 1].job].in_degree--;
            if (machine_node_list[target_order->operations[node->job][node->operation->index + 1].machine]
                [target_order->operations[node->job][node->operation->index + 1].job].in_degree == 0) {
                push(zero_degree, &machine_node_list[target_order->operations[node->job][node->operation->index + 1].machine]
                    [target_order->operations[node->job][node->operation->index + 1].job]);
            }
        }
        if (scheduled[node->machine]) {
            size_t i = 0;
            while (machine_schedule[node->machine]->data[i] != node->job) {
                if (machine_node_list[node->machine][machine_schedule[node->machine]->data[i]].r
                    + machine_node_list[node->machine][machine_schedule[node->machine]->data[i]].p
                    > max_length) {
                    max_length = machine_node_list[node->machine][machine_schedule[node->machine]->data[i]].r
                        + machine_node_list[node->machine][machine_schedule[node->machine]->data[i]].p;
                }
                i++;
            }
            i++;
            while (i < size(machine_schedule[node->machine])) {
                machine_node_list[node->machine][machine_schedule[node->machine]->data[i]].in_degree--;
                if (machine_node_list[node->machine][machine_schedule[node->machine]->data[i]].in_degree == 0) {
                    push(zero_degree, &machine_node_list[node->machine][machine_schedule[node->machine]->data[i]]);
                }
                i++;
            }
        }
        node->r = max_length;
 //       printf("(%d,%d).r->%d\n", node->machine + 1, node->job + 1, node->r);
    }
    // Calculate q_i
    // 初始化入度
    for (size_t index = 0; index < target_order->num_of_machines; index++) {
        for (size_t node_index = 0; node_index < size(machine_schedule[index]); node_index++) {
            if (machine_node_list[index][machine_schedule[index]->data[node_index]].operation != NULL) {
                machine_node_list[index][machine_schedule[index]->data[node_index]].in_degree = 1;
                if (scheduled[index]) {
                    machine_node_list[index][machine_schedule[index]->data[node_index]].in_degree += size(machine_schedule[index]) - node_index - 1;
                }
                if (machine_node_list[index][machine_schedule[index]->data[node_index]].operation->index == target_order->operations_of_jobs[machine_node_list[index][machine_schedule[index]->data[node_index]].job] - 1) {
                    machine_node_list[index][machine_schedule[index]->data[node_index]].in_degree--;
                }
                if (machine_node_list[index][machine_schedule[index]->data[node_index]].in_degree == 0) {
                    machine_node_list[index][machine_schedule[index]->data[node_index]].q = 0;
                    push(zero_degree, &machine_node_list[index][machine_schedule[index]->data[node_index]]);
                }
                else {
                    machine_node_list[index][machine_schedule[index]->data[node_index]].q = INT_MAX;
                }
            }
        }
    }
    while (!is_empty(zero_degree)) {
        p_node_t node = front(zero_degree);
        pop(zero_degree);
        // update release time
        int max_length = node->operation->index == target_order->operations_of_jobs[node->job] - 1 ? 0
            : machine_node_list[target_order->operations[node->job][node->operation->index + 1].machine]
            [target_order->operations[node->job][node->operation->index + 1].job].q
            + target_order->operations[node->job][node->operation->index + 1].period;
        if (node->operation->index != 0) {
            machine_node_list[target_order->operations[node->job][node->operation->index - 1].machine]
                [target_order->operations[node->job][node->operation->index - 1].job].in_degree--;
            if (machine_node_list[target_order->operations[node->job][node->operation->index + 1].machine]
                [target_order->operations[node->job][node->operation->index - 1].job].in_degree == 0) {
                push(zero_degree, &machine_node_list[target_order->operations[node->job][node->operation->index - 1].machine]
                    [target_order->operations[node->job][node->operation->index - 1].job]);
            }
        }
        if (scheduled[node->machine]) {
            size_t i = size(machine_schedule[node->machine]) - 1;
            while (machine_schedule[node->machine]->data[i] != node->job) {
                if (machine_node_list[node->machine][machine_schedule[node->machine]->data[i]].q
                    + machine_node_list[node->machine][machine_schedule[node->machine]->data[i]].p
        > max_length) {
                    max_length = machine_node_list[node->machine][machine_schedule[node->machine]->data[i]].q
                        + machine_node_list[node->machine][machine_schedule[node->machine]->data[i]].p;
                }
                i--;
            }
            i--;
            while ((int)i >= 0) {
                machine_node_list[node->machine][machine_schedule[node->machine]->data[i]].in_degree--;
                if (machine_node_list[node->machine][machine_schedule[node->machine]->data[i]].in_degree == 0) {
                    push(zero_degree, &machine_node_list[node->machine][machine_schedule[node->machine]->data[i]]);
                }
                i--;
            }
        }
        node->q = max_length;
//        printf("(%d,%d).q->%d\n", node->machine + 1, node->job + 1, node->q);
    }
}

int calculate_machine_makespan(int k) {
    for (int i = 0; i < target_order->num_of_jobs; i++) {
        if (machine_node_list[k][i].operation != NULL) {
            machine_node_list[k][i].in_u = false;
        }
    }
    int t = INT_MAX;
    for (int i = 0; i < target_order->num_of_jobs; i++) {
        if (machine_node_list[k][i].operation != NULL && machine_node_list[k][i].r < t) {
            t = machine_node_list[k][i].r;
        }
    }
}

int determain_bottleneck_machine() {
    longest_path();
    int max_makespan = INT_MIN;
    int k = -1;
    for (size_t i = 0; i < target_order->num_of_machines; i++) {
        if (!scheduled[i]) {
            int makespan = calculate_machine_makespan(i);
            if (max_makespan < makespan) {
                max_makespan = makespan;
                k = i;
            }
        }
    }
    return k;
}

void reschedule_scheduled_machines() {

}

void shifting_bottleneck_heuristic_optimize() {
   /* scheduled[2] = true;
    machine_schedule[2]->data[0] = 1;
    machine_schedule[2]->data[1] = 0;
    machine_schedule[2]->data[2] = 2;*/
    size_t scheduled_machine_count = 0;
    while (scheduled_machine_count < target_order->num_of_machines) {
        int m = determain_bottleneck_machine();
        scheduled[m] = true;
        scheduled_machine_count++;
        reschedule_scheduled_machines();
    }
}
