/**
 * @brief Implementation of genetic_optimizer.h.
 * 
 * @file genetic_optimizer.c
 * @author Jason Qiu, Celery Meng
 * @date 2018-05-17
 */
#include "genetic_optimizer.h"

#include "../base.h"
#include "chromosome_pool.h"

#include <assert.h>

extern p_order_t target_order;

int population_density = 0;
double reproductive_rate = 0.;
p_chromosome_t template_chromosome = NULL;
p_array_t(p_chromosome_t) population = NULL;

/**
 * @private
 * @brief 比较两个给定染色体的适应度。
 * 
 * @param a 给定染色体。
 * @param b 给定染色体。
 * @return int 比较结果。
 */
int compare_chromosome_makespan(const void *a, const void *b);
/**
 * @private
 * @brief 随机洗牌给定染色体的基因。
 * 
 * @param chromosome 给定染色体。
 */
void shuffle(p_chromosome_t chromosome);
/**
 * @private
 * @brief 初始化种群。
 * 
 */
void initialize_population();
/**
 * @private
 * @brief 获得一个随机染色体。
 * 
 */
p_chromosome_t get_random_chromosome();
/**
 * @private
 * @brief GOX 交叉算子。
 * 
 * @param father 父代染色体。
 * @param mother 母代染色体。
 */
p_chromosome_t GOX(p_chromosome_t father, p_chromosome_t mother);



int compare_chromosome_makespan(const void *a, const void *b) {
    assert(((p_chromosome_t)a)->makespan != MAKESPAN_UNCALCULATED);
}

void shuffle(p_chromosome_t chromosome) {
    // TODO: Implent it
}

void initialize_genetic_optimizer(int density, double rate) {
    population_density = density;
    reproductive_rate = rate;
    initialize_chromosome_pool((size_t)(2 * density * (1 + reproductive_rate)));
    initialize_population();
}

void destroy_genetic_optimizer() {
    assert(population != NULL);
    delete_array(population);
    
    destroy_chromosome_pool();
}

void initialize_population() {
    population = new_array(p_chromosome_t, population_density * 2);
    template_chromosome = new_chromosome();
    // TODO: Initialize template_chromosome
    for (int i = 0; i < population_density; i++) {
        push_back(population, get_random_chromosome());
    }
}

p_chromosome_t get_random_chromosome() {
    p_chromosome_t res = new_chromosome_copy_from(template_chromosome);
    shuffle(res);
    return res;
}

p_chromosome_t GOX(p_chromosome_t father, p_chromosome_t mother) {
    // TODO: Implent it
    p_chromosome_t child = new_chromosome();
    mutate(child);
    return child;
}

void evolve() {
    GOX(NULL, NULL);
    qsort(begin(population), size(population), sizeof(front(population)), compare_chromosome_makespan);
    delete_chromosome(NULL);
}

void genetic_optimize() {
    evolve();
}


