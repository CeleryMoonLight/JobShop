/**
 * @brief Genetic optimizer.
 * 
 * @file genetic_optimizer.h
 * @author Jason Qiu
 * @date 2018-05-18
 */
#ifndef _GENETIC_OPTIMIZER_H_
#define _GENETIC_OPTIMIZER_H_

/**
 * @public
 * @brief Initializes the genetic optimizer. 
 * 
 * @param density Population Density.
 * @param rate Reproductive rate of the population. 
 */
void initialize_genetic_optimizer(int density, double rate);
/**
 * @public
 * @brief Destroys the genetic optimizer. 
 * 
 */
void destroy_genetic_optimizer();
/**
 * @public
 * @brief Optimizes the order by one interation using the genetic optimizer. 
 * 
 */
void genetic_optimize(int epoch);

#endif
