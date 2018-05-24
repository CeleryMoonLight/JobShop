/**
 * @brief 定义有关染色体的数据类型与操作。
 * 
 * @file chromosome.h
 * @author Jason Qiu
 * @date 2018-05-18
 */
#ifndef _CHROMOSOME_H_
#define _CHROMOSOME_H_

#include "../base.h"

/**
 * @brief 表示一个染色体。
 * 
 */
typedef struct {
    int *genes;         /**< @brief 表示该染色体的基因。 */
    int *indexes;       /**< @brief 表示该染色体基因对应的工序序号。 */
    size_t size;           /**< @brief 表示该染色体的基因长度。 */
    int makespan;       /**< @brief 表示该染色体的总完工时间。 */
} chromosome_t;

/**
 * @brief chromosome_t 指针。
 * 
 */
typedef chromosome_t *p_chromosome_t;

/**
 * @brief 初始化给定染色体。
 * 
 * @param chromosome 给定染色体。
 */
void initialize_chromosome(p_chromosome_t chromosome, size_t size);
/**
 * @brief 销毁给定染色体。
 * 
 * @param chromosome 给定染色体。
 */
void destroy_chromosome(p_chromosome_t chromosome);
/**
 * @brief 计算给定染色体的工序序号。
 * 
 * @param chromosome 给定染色体。
 */
void calculate_indexes(p_chromosome_t chromosome);
/**
 * @brief 解码给定染色体。
 * 
 * @param chromosome 给定染色体。
 */
void decode(p_chromosome_t chromosome);
/**
 * @brief 返回给定染色体的总完工时间。
 * 
 * @param chromosome 给定染色体。
 * @return 总完工时间。
 */
int makespan(p_chromosome_t chromosome);
/**
 * @brief 变异给定染色体。
 * 
 * @param chromosome 给定染色体。
 */
void mutate(p_chromosome_t chromosome);

#endif // !_CHROMOSOME_H_