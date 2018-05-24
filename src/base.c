/**
 * @brief Implementation of base.h.
 * 
 * @file base.c
 * @author Celery Meng
 * @date 2018-05-03
 */
#include "base.h"

p_order_t new_order() {
    return (p_order_t)malloc(sizeof(order_t));
}

void delete_order(p_order_t order)
{
    for (int i = 0; i < order->num_of_jobs; i++) {
        free(order->operations[i]);
    }
    free(order->operations);
    free(order);
}
