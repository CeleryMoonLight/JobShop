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

extern p_order_t target_order;

int population_density = 0;
double reproductive_rate = 0.;
p_chromosome_t template_chromosome = NULL;

int compare_chromosome_makespan(p_chromosome_t a, p_chromosome_t b) {
    return makespan(a) < makespan(b);
}

void shuffle() {

}

void initialize_genetic_optimizer(int density, double rate) {
    population_density = density;
    reproductive_rate = rate;
    initialize_chromosome_pool((size_t)(2 * density * (1 + reproductive_rate)));
    initialize_population();
}

void destroy_genetic_optimizer() {
    destroy_chromosome_pool();
}

void initialize_population() {
    template_chromosome = new_chromosome();

    get_random_chromosome();
    
}

p_chromosome_t get_random_chromosome() {
    new_chromosome_copy_from(NULL);
    shuffle();
}

p_chromosome_t GOX(p_chromosome_t father, p_chromosome_t mother) {
    p_chromosome_t child = new_chromosome();
    mutate(child);
    return child;
}

void evolve() {
    GOX(NULL, NULL);
    delete_chromosome(NULL);
}

void genetic_optimize() {
    evolve();
}


