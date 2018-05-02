/**
 * @brief 此文件定义了基本数据结构类型与操作。
 * 
 * @file file.h
 * @author Jason Qiu
 * @date 2018-05-02
 */

#ifndef _BASE_H_
#define _BASE_H_

#define IN                  /**< 表示该函数参数为输入 */
#define OUT                 /**< 表示该函数参数为输出 */

/**
 * @brief 表示一项工序
 * 
 */
typedef struct _operation {
    int job;                /**< 该工序所属的产品 */
    int period;             /**< 该工序所需的时间 */
    int machine;            /**< 该工序指定的机器 */
} operation;

/**
 * @brief 表示订单
 * @note operations 在读入数据时初始化，在 order 销毁时销毁。
 */
typedef struct _order {
    operation **operations; /**< 储存所有工序的指针数组 */
    int num_of_jobs;        /**< 共有多少个产品 */
    int num_of_machines;    /**< 共有多少台机器 */
} order;

/**
 * @brief 创建 order 对象
 * 
 * @return order* 指向创建的 order 对象的指针
 */
order *new_order(
);

/**
 * @brief 销毁 order 对象
 * 
 * @param order 
 */
void delete_order(
    OUT order *to_be_deleted
);

#endif // !_BASE_H_
