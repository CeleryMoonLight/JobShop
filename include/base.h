/**
 * @brief Defines the basic data structures and functions.
 * 
 * @file base.h
 * @author Jason Qiu
 * @date 2018-05-02
 */

#ifndef _BASE_H_
#define _BASE_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

/**
 * @brief Represents an operation of a job. 
 * 
 */
typedef struct {
    int job;                /**< @brief The job to which this operation belongs. */
    int period;             /**< @brief How long will this operation be processed. */
    int machine;            /**< @brief The machine on which this operation will be processed. */
    int index;              /**< @brief The index of this operation. */
    int begin_time;         /**< @brief Scheduled start time of this operation. */
    int end_time;           /**< @brief Scheduled end time of this operation. */
} operation_t;

/**
 * @brief Pointer to operation_t.
 * 
 */
typedef operation_t *p_operation_t;

/**
 * @brief Represents an order.
 * @note operations are initialized while reading the input data, 
 * destroyed when order_t is destroyed.
 */
typedef struct {
    p_operation_t *operations;     /**< @brief Stores all operations. */
    size_t *operations_of_jobs;    /**< @brief The number of operations of a specified job. */
    size_t num_of_operations;      /**< @brief The number of all operations. */
    size_t num_of_jobs;            /**< @brief The number of jobs. */
    size_t num_of_machines;        /**< @brief The number of machines. */
    int makespan;                  /**< @brief Final makespan of the scheduling result. */
} order_t;

/**
 * @brief Pointer to order_t.
 * 
 */
typedef order_t *p_order_t;

/**
 * @public
 * @brief Creates an object of order_t.
 * 
 * @return p_order_t Pointer to the new order_t object. 
 */
p_order_t new_order();

/**
 * @public
 * @brief Destroys an order_t object.
 * 
 * @param order order that to be destroyed.
 */
void delete_order(p_order_t order);

#endif // !_BASE_H_
