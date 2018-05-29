/**
 * @brief Utility functions.
 * 
 * @file util.h
 * @author Jason Qiu
 * @date 2018-05-25
 */
#ifndef _UTIL_H_
#define _UTIL_H_

#include "base.h"

/**
 * @public
 * @brief Swaps two integers.
 * 
 * @param a First element.
 * @param b Second element.
 */
void swap_int(int *a, int *b);
/**
 * @brief Swaps two size_t variables.
 * 
 * @param a First element.
 * @param b Second element.
 */
void swap_size_t(size_t *a, size_t *b);
/**
 * @public
 * @brief Initializes the random engine using the system time.
 * 
 */
void initialize_random_engine();
/**
 * @public
 * @brief Initializes the random engine using the given seed.
 * 
 * @param seed Given seed.
 */
void initialize_random_engine_with_seed(unsigned int seed);

/**
 * @public
 * @brief Generates random integers of uniform distribution.
 * 
 * @param lower_bound Lower bound.
 * @param upper_bound Upper bound.
 * @return int Random integer of uniform distribution.
 */
int uniform_int_distribution(int lower_bound, int upper_bound);

/**
 * @public
 * @brief Generates random doubles of normal distribution.
 * 
 * @param mean Mean (μ).
 * @param stddev Standard Deviation (σ).
 * @return double Random double of uniform distribution.
 */
double normal_distribution(double mean, double stddev);

#endif // !_UTIL_H_