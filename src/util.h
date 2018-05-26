/**
 * @brief 实用函数。
 * 
 * @file util.h
 * @author Jason Qiu
 * @date 2018-05-25
 */
#ifndef _UTIL_H_
#define _UTIL_H_

/**
 * @public
 * @brief 交换两个元素。
 * 
 * @param a 第一个元素。
 * @param b 第二个元素。
 */
void swap(int *a, int *b);
/**
 * @public
 * @brief 利用当前系统时间初始化随机数引擎。
 * 
 */
void initialize_random_engine();
/**
 * @public
 * @brief 利用给定种子初始化随机数引擎。
 * 
 * @param seed 给定种子。
 */
void initialize_random_engine_with_seed(unsigned int seed);

/**
 * @public
 * @brief 产生均匀分布整型随机数。
 * 
 * @param lower_bound 下界。
 * @param upper_bound 上界。
 * @return int 均匀分布随机数。
 */
int uniform_int_distribution(int lower_bound, int upper_bound);

/**
 * @public
 * @brief 产生正态分布浮点型随机数。
 * 
 * @param mean 正态分布的参数 μ（均值）。
 * @param stddev 正态分布的参数 σ（标准差）。
 * @return double 正态分布随机数。
 */
double normal_distribution(double mean, double stddev);

#endif // !_UTIL_H_