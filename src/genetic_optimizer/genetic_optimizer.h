/**
 * @brief 遗传算法优化器。
 * 
 * @file genetic_optimizer.h
 * @author Jason Qiu
 * @date 2018-05-18
 */
#ifndef _GENETIC_OPTIMIZER_H_
#define _GENETIC_OPTIMIZER_H_

/**
 * @public
 * @brief 初始化遗传算法优化器。
 * 
 * @param density 种群密度。
 * @param rate 种群繁殖率。
 */
void initialize_genetic_optimizer(int density, double rate);
/**
 * @public
 * @brief 销毁遗传算法优化器。
 * 
 */
void destroy_genetic_optimizer();
/**
 * @public
 * @brief 利用遗传算法优化器迭代一次。
 * 
 */
void genetic_optimize();

#endif