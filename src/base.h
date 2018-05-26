/**
 * @brief 定义基本数据结构类型与操作。
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


/**
 * @brief 表示一项工序。
 * 
 */
typedef struct {
    int job;                /**< @brief 表示该工序所属的产品。 */
    int period;             /**< @brief 表示该工序所需的时间。 */
    int machine;            /**< @brief 表示该工序指定的机器。 */
    int begin_time;         /**< @brief 表示该工序的开始时间。 */
    int end_time;           /**< @brief 表示该工序的结束时间。 */
} operation_t;

/**
 * @brief operation_t 指针。
 * 
 */
typedef operation_t *p_operation_t;

/**
 * @brief 表示订单。
 * @note operations 在读入数据时初始化，在 order_t 销毁时销毁。
 */
typedef struct {
    p_operation_t *operations;     /**< @brief 储存所有 operation_t 的指针数组。 */
    size_t *operations_of_jobs;    /**< @brief 表示单个指定产品的工序数。 */
    size_t num_of_operations;      /**< @brief 表示所有产品共有多少个工序。 */
    size_t num_of_jobs;            /**< @brief 表示共有多少个产品。 */
    size_t num_of_machines;        /**< @brief 表示共有多少台机器。 */
} order_t;

/**
 * @brief order_t 指针。
 * 
 */
typedef order_t *p_order_t;

/**
 * @public
 * @brief 创建 order_t 对象。
 * 
 * @return p_order_t 指向创建的 order_t 对象的指针。
 * @author Celery Meng
 */
p_order_t new_order();

/**
 * @public
 * @brief 销毁 order_t 对象。
 * 
 * @param order 要被销毁的 order_t 对象。
 * @author Celery Meng
 */
void delete_order(p_order_t order);

#endif // !_BASE_H_
