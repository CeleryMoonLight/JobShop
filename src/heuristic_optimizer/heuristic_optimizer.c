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
    machine_schedule = (p_array_t(int))calloc(target_order->num_of_machines, sizeof(p_array_t(int)));
    for (int index = 0; index < target_order->num_of_machines; index++) {
        machine_schedule[index] = new_array(int, target_order->num_of_jobs);
    }
    machine_node_list = (p_node_t *)calloc(target_order->num_of_machines, sizeof(p_node_t *));
    for (int index = 0; index < target_order->num_of_machines; index++) {
        machine_node_list[index] = (p_node_t)calloc(target_order->num_of_jobs, sizeof(p_node_t));
    }
    for (size_t i = 0; i < target_order->num_of_jobs; i++) {
        for (size_t j = 0; j < target_order->operations_of_jobs[i]; j++) {
            machine_node_list[target_order->operations[i][j].machine][i].machine = target_order->operations[i][j].machine;
            machine_node_list[target_order->operations[i][j].machine][i].job = target_order->operations[i][j].job;
            machine_node_list[target_order->operations[i][j].machine][i].p = target_order->operations[i][j].period;
            machine_node_list[target_order->operations[i][j].machine][i].operation = &(target_order->operations[i][j]);
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

int longest_path() {
    // 初始化入度
    for (size_t index = 0; index < target_order->num_of_machines; index++) {
        for (size_t node_index = 0; node_index < size(machine_schedule[index]); node_index++) {
            if (machine_node_list[index][machine_schedule[index]->data[node_index]].operation != NULL) {
                machine_node_list[index][machine_schedule[index]->data[node_index]].in_degree = 1;
                if (scheduled[index]) {
                    machine_node_list[index][machine_schedule[index]->data[node_index]].in_degree += node_index;
                }
                if (machine_node_list[index][machine_schedule[index]->data[node_index]].in_degree == 1) {
                    machine_node_list[index][machine_schedule[index]->data[node_index]].in_degree = 0;
                    machine_node_list[index][machine_schedule[index]->data[node_index]].r = 0;
                    push(zero_degree, &machine_node_list[index][node_index]);
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
        int max_length = node->operation->index == 0 ? INT_MAX 
        : machine_node_list[target_order->operations[node->job][node->operation->index - 1].machine]
                            [target_order->operations[node->job][node->operation->index - 1].job].r
                            + target_order->operations[node->job][node->operation->index - 1].period;
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
        
        node->r = max_length;
    }
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
