/**
 * @brief Chromosome object pool.
 * 
 * @file chromosome_pool.h
 * @author Jason Qiu
 * @date 2018-05-18
 */
#ifndef _CHROMOSOME_POOL_H_
#define _CHROMOSOME_POOL_H_

#include "chromosome.h"

/**
 * @public
 * @brief Initializes the object pool.
 * 
 * @param capacity Capacity of the object pool.
 */
void initialize_chromosome_pool(size_t capacity);
/**
 * @public
 * @brief Destroys the object pool.
 * 
 */
void destroy_chromosome_pool();
/**
 * @public
 * @brief Gets a new object from the pool.
 * 
 */
p_chromosome_t new_chromosome();
/**
 * @public
 * @brief Gets a new chromosome, copies the specified chromosome to the new chromosome.
 * 
 * @param chromosome Specified chromosome.
 */
p_chromosome_t new_chromosome_copy_from(p_chromosome_t chromosome);
/**
 * @public
 * @brief Returns the specified chromosome to the pool.
 * 
 * @param chromosome Specified chromosome.
 */
void delete_chromosome(p_chromosome_t chromosome);

#endif // !_CHROMOSOME_POOL_H_
