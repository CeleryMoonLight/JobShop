/**
 * @brief Structures and functions of chromosomes.
 * 
 * @file chromosome.h
 * @author Jason Qiu
 * @date 2018-05-18
 */
#ifndef _CHROMOSOME_H_
#define _CHROMOSOME_H_

#include "../base.h"

#define MAKESPAN_UNCALCULATED -1

/**
 * @brief Represents a chromosome.
 * 
 */
typedef struct {
    int *genes;         /**< @brief Represents genes of this chromosome. */
    int *indexes;       /**< @brief Represents the corresponding operation indexes of this chromosome. */
    size_t size;        /**< @brief The length of this chromosome. */
    int makespan;       /**< @brief The corresponding makespan of this chromosome. */
} chromosome_t;

/**
 * @brief Pointer to chromosome_t.
 * @sa chromosome_t
 */
typedef chromosome_t *p_chromosome_t;

/**
 * @public
 * @brief Initializes the specified chromosome with the given length.
 * 
 * @param chromosome Specified chromosome.
 * @param size Given length of the chromosome.
 */
void initialize_chromosome(p_chromosome_t chromosome, size_t size);
/**
 * @public
 * @brief Destroys the specified chromosome.
 * 
 * @param chromosome Specified chromosome.
 */
void destroy_chromosome(p_chromosome_t chromosome);
/**
 * @public
 * @brief Calculates the corresponding operation indexes of the specified chromosome.
 * 
 * @param chromosome Specified chromosome.
 */
void calculate_indexes(p_chromosome_t chromosome);
/**
 * @public
 * @brief Decodes the specified chromosome.
 * 
 * @param chromosome Specified chromosome.
 */
void decode(p_chromosome_t chromosome);
/**
 * @public
 * @brief Returns the makespan of the specified chromosome.
 * 
 * @param chromosome Specified chromosome.
 * @return Makespan.
 */
int makespan(p_chromosome_t chromosome);
/**
 * @public
 * @brief Mutation Operator.
 * 
 * @param chromosome Specified chromosome.
 */
void mutate(p_chromosome_t chromosome);

#endif // !_CHROMOSOME_H_
