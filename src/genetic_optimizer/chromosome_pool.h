/**
 * @brief 染色体对象池。
 * 
 * @file chromosome_pool.h
 * @author Jason Qiu
 * @date 2018-05-18
 */
#ifndef _CHROMOSOME_POOL_H_
#define _CHROMOSOME_POOL_H_

#include "chromosome.h"
#include "../ADT/queue.h"
#include "../ADT/interface.h"

define_queue(p_chromosome_t);

/**
 * @brief 初始化对象池。
 * 
 * @param capacity 对象池大小。
 */
void initialize_chromosome_pool(size_t capacity);
/**
 * @brief 销毁对象池。
 * 
 */
void destroy_chromosome_pool();
/**
 * @brief 从对象池获得染色体对象并返回。
 * 
 */
p_chromosome_t new_chromosome();
/**
 * @brief 拷贝构造染色体对象并返回。
 * 
 * @param chromosome 给定染色体。
 */
p_chromosome_t new_chromosome_copy_from(p_chromosome_t chromosome);
/**
 * @brief 回收给定染色体。
 * 
 * @param chromosome 给定染色体。
 */
void delete_chromosome(p_chromosome_t chromosome);

#endif // !_CHROMOSOME_H_
