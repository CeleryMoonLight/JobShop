/**
 * @brief Implentation of chromosome_pool.h
 * 
 * @file chromosome_pool.c
 * @author Jason Qiu, Celery Meng
 * @date 2018-05-18
 */
#include "chromosome_pool.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../base.h"

extern p_order_t target_order;

p_queue_t(p_chromosome_t) pointer_queue = NULL;
p_chromosome_t memory_pool = NULL;
size_t pool_capacity = 0;

void initialize_chromosome_pool(size_t capacity) {
    pool_capacity = capacity;
    pointer_queue = new_queue(p_chromosome_t, pool_capacity);
    memory_pool = (p_chromosome_t)calloc(pool_capacity, sizeof(chromosome_t));
    for (p_chromosome_t pointer = memory_pool; pointer < memory_pool + pool_capacity; pointer++) {
        initialize_chromosome(pointer, target_order->num_of_operations);
        push(pointer_queue, pointer);
    }
}

void destroy_chromosome_pool() {
    delete_queue(pointer_queue);
    pointer_queue = NULL;
    for (p_chromosome_t pointer = memory_pool; pointer < memory_pool + pool_capacity; pointer++) {
        destroy_chromosome(pointer);
    }
    free(memory_pool);
    memory_pool = NULL;
}

p_chromosome_t new_chromosome() {
    p_chromosome_t res = front(pointer_queue);
    pop(pointer_queue);
    return res;
}

p_chromosome_t new_chromosome_copy_from(p_chromosome_t chromosome) {
    p_chromosome_t res = new_chromosome();
    memcpy(res->genes, chromosome->genes, chromosome->size);
    memcpy(res->indexes, chromosome->indexes, chromosome->size);
    res->makespan = chromosome->makespan;
    return res;
}

void delete_chromosome(p_chromosome_t chromosome) {
    push(pointer_queue, chromosome);
}