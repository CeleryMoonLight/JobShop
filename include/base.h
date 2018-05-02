/**
 * @brief 定义基本数据结构类型与操作。
 * 
 * @file base.h
 * @author Jason Qiu
 * @date 2018-05-02
 */

#ifndef _BASE_H_
#define _BASE_H_

#define IN                  /**< @brief 表示该函数参数为输入。 */
#define OUT                 /**< @brief 表示该函数参数为输出。 */

/**
 * @brief 表示一项工序。
 * 
 */
typedef struct {
    int job;                /**< @brief 表示该工序所属的产品。 */
    int period;             /**< @brief 表示该工序所需的时间。 */
    int machine;            /**< @brief 表示该工序指定的机器。 */
} operation_t;

/**
 * @brief 表示订单。
 * @note operations 在读入数据时初始化，在 order_t 销毁时销毁。
 */
typedef struct {
    operation **operations; /**< @brief 储存所有 operation_t 的指针数组。 */
    int num_of_jobs;        /**< @brief 表示共有多少个产品。 */
    int num_of_machines;    /**< @brief 表示共有多少台机器。 */
} order_t;

/**
 * @brief 创建 order_t 对象。
 * 
 * @return order_t* 指向创建的 order_t 对象的指针。
 */
order_t *new_order(
);

/**
 * @brief 销毁 order_t 对象。
 * 
 * @param to_be_deleted 要被销毁的 order_t 对象。
 */
void delete_order(
    IN OUT order_t *to_be_deleted
);

#endif // !_BASE_H_
