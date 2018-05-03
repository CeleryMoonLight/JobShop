/**
 * @brief Implementation of base.h
 * 
 * @file base.c
 * @author Celery Meng
 * @date 2018-05-03
 */
#include "base.h"

order_t *new_order() {
    return (order_t*)malloc(sizeof(order_t));
}

void delete_order(order_t *to_be_deleted)
{
    for (int i = 0; i < to_be_deleted->num_of_jobs; i++) {
        free(to_be_deleted->operations[i]);
    }
    free(to_be_deleted->operations);
    free(to_be_deleted);
}
