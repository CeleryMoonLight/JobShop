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
#include "../ADT/ADT.h"

define_array(p_chromosome_t);

extern p_order_t target_order;

int population_density = 0;
double reproductive_rate = 0.;
p_chromosome_t template_chromosome = NULL;
p_array_t(p_chromosome_t) population = NULL;
bool *is_copyable = NULL;
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
    assert(((p_chromosome_t)b)->makespan != MAKESPAN_UNCALCULATED);
    return ((p_chromosome_t)b)->makespan - ((p_chromosome_t)a)->makespan;
}

void shuffle(p_chromosome_t chromosome) {
    // TODO: Implement it
    chromosome->makespan = MAKESPAN_UNCALCULATED;
}

void initialize_genetic_optimizer(int density, double rate) {
    population_density = density;
    reproductive_rate = rate;
    is_copyable = (int *)calloc(target_order->num_of_operations, sizeof(int));
    initialize_chromosome_pool((size_t)(2 * density * (1 + reproductive_rate)));
    // Initialize template chromosome
    template_chromosome = new_chromosome();
    int *current_gene = template_chromosome->genes;
    for (size_t job_index = 0; job_index < target_order->num_of_jobs; job_index++) {
        for (size_t count = 0; count < target_order->operations_of_jobs[job_index]; count++) {
            *current_gene = (int)job_index;
            current_gene++;
        }
    }
    initialize_population();
}

void destroy_genetic_optimizer() {
    delete_array(population);
    assert(is_copyable != NULL);
    free(is_copyable);
    is_copyable = NULL;
    destroy_chromosome_pool();
}

void initialize_population() {
    population = new_array(p_chromosome_t, population_density * 2);
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
    p_chromosome_t child = new_chromosome();
    size_t i = 0;  //TODO: rand
    size_t j = 0;  //TODO: rand
    size_t k = 0;  //TODO: rand
    if (i > j) {
        swap(i, j); //TODO: swap!!
    }
    memset(is_copyable, true, father->size * sizeof(bool));
    for (size_t father_index = 0; father_index < father->size; father_index++) {
        for (size_t mother_index = i; mother_index <= j; mother_index++) {
            if (father->genes[father_index] == mother->genes[mother_index] &&
                father->indexes[father_index] == mother->indexes[mother_index]) {
                is_copyable[father_index] = false;
                break;
            }
        }
    }
    int *current_gene = child->genes;
    for (size_t index = 0; index < k; index++) {
        if (is_copyable[index]) {
            *current_gene = father->genes[index];
            current_gene++;
        }
    }
    for (size_t index = i; index <= j; index++) {
        *current_gene = mother->genes[index];
        current_gene++;
    }
    for (size_t index = k; index < father->size; index++) {
        if (is_copyable[index]) {
            *current_gene = father->genes[index];
            current_gene++;
        }
    }
    mutate(child);  // TODO: 
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


