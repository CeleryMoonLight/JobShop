/**
 * @brief Implementation of chromosome.h.
 * 
 * @file chromosome.c
 * @author Jason Qiu, Celery Meng
 * @date 2018-05-03
 */
#include "chromosome.h"

#include "../base.h"
#include "../util.h"

int *index_count;
int *machine_end_time;
extern p_order_t target_order;

void initialize_chromosome(p_chromosome_t chromosome, size_t size) {
    chromosome->size = size;
    chromosome->genes = (int *)calloc(chromosome->size, sizeof(int));
    chromosome->indexes = (int *)calloc(chromosome->size, sizeof(int)); 
    chromosome->makespan = MAKESPAN_UNCALCULATED;
}

void destroy_chromosome(p_chromosome_t chromosome) {
    assert(chromosome->genes != NULL);
    free(chromosome->genes);
    chromosome->genes = NULL;
    assert(chromosome->indexes != NULL);
    free(chromosome->indexes);
    chromosome->indexes = NULL;
}

void calculate_indexes(p_chromosome_t chromosome) {
    memset(index_count, 0, target_order->num_of_jobs * sizeof(int));
    for (size_t index = 0; index < chromosome->size; index++) {
        chromosome->indexes[index] = index_count[chromosome->genes[index]];
        index_count[chromosome->genes[index]]++;
    }
}

void decode(p_chromosome_t chromosome) {
    calculate_indexes(chromosome);
    memset(machine_end_time, 0, target_order->num_of_machines * sizeof(int));
    chromosome->makespan = 0;
    p_operation_t *ops = target_order->operations;
    for (size_t i = 0; i < chromosome->size; i++) {
        int g = chromosome->genes[i];
        if (chromosome->indexes[i] != 0) {
            ops[g][chromosome->indexes[i]].begin_time = max(machine_end_time[ops[g][chromosome->indexes[i]].machine], ops[g][chromosome->indexes[i] - 1].end_time);
        } else {
            ops[g][chromosome->indexes[i]].begin_time = machine_end_time[ops[g][chromosome->indexes[i]].machine];            
        }
        ops[g][chromosome->indexes[i]].end_time = ops[g][chromosome->indexes[i]].begin_time + ops[g][chromosome->indexes[i]].period;
        machine_end_time[ops[g][chromosome->indexes[i]].machine] = ops[g][chromosome->indexes[i]].end_time;
        if (ops[g][chromosome->indexes[i]].end_time > chromosome->makespan) {
            chromosome->makespan = ops[g][chromosome->indexes[i]].end_time;
        }
    }
}

int makespan(p_chromosome_t chromosome) {
    if (chromosome->makespan == MAKESPAN_UNCALCULATED) {
        decode(chromosome);
    }
    return chromosome->makespan;
}

void mutate(p_chromosome_t chromosome) {
    //TODO: random version
    size_t i = 0;   // random things...
    size_t j = 0;
    swap(&chromosome->genes[i], &chromosome->genes[j]);
    chromosome->makespan = MAKESPAN_UNCALCULATED;
}