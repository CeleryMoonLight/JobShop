/**
 * @brief 遗传算法优化器。
 * 
 * @file genetic_optimizer.h
 * @author Jason Qiu
 * @date 2018-05-18
 */
#ifndef _GENETIC_OPTIMIZER_H_
#define _GENETIC_OPTIMIZER_H_

#include "chromosome.h"
#include "chromosome_pool.h"

/**
 * @brief 初始化遗传算法优化器。
 * 
 * @param density 种群密度。
 * @param rate 种群繁殖率。
 */
void initialize_genetic_optimizer(int density, double rate);
/**
 * @brief 销毁遗传算法优化器。
 * 
 */
void destroy_genetic_optimizer();
/**
 * @brief 初始化种群。
 * 
 */
void initialize_population();
/**
 * @brief 获得一个随机染色体。
 * 
 */
p_chromosome_t get_random_chromosome();
/**
 * @brief GOX 交叉算子。
 * 
 * @param father 父代染色体。
 * @param mother 母代染色体。
 */
p_chromosome_t GOX(p_chromosome_t father, p_chromosome_t mother);

/**
 * @brief 利用遗传算法优化器迭代一次。
 * 
 */
void genetic_optimize();

#endif