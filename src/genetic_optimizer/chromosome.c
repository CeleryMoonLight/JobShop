/**
 * @brief Implementation of chromosome.h.
 * 
 * @file chromosome.c
 * @author Jason Qiu, Celery Meng
 * @date 2018-05-03
 */
#include "chromosome.h"
#include <stddef.h>
#include <assert.h>

#define MAKESPAN_UNCALCULATED -1

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
    //TODO
}

void decode(p_chromosome_t chromosome) {
    calculate_indexes(chromosome);
    // TODO
}

int makespan(p_chromosome_t chromosome) {
    if (chromosome->makespan == MAKESPAN_UNCALCULATED) {
        decode(chromosome);
    }
    return chromosome->makespan;
}

void mutate(p_chromosome_t chromosome) {
    // TODO
    chromosome->makespan = MAKESPAN_UNCALCULATED;
}