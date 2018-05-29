/**
 * @brief Implementation of genetic_optimizer.h.
 * 
 * @file genetic_optimizer.c
 * @author Celery Meng, Jason Qiu
 * @date 2018-05-17
 */
#include "genetic_optimizer/genetic_optimizer.h"

#include "base.h"
#include "genetic_optimizer/chromosome_pool.h"
#include "ADT/ADT.h"
#include "util.h"

define_array(p_chromosome_t);

extern p_order_t target_order;

int population_density = 0;
double reproductive_rate = 0.;
p_chromosome_t template_chromosome = NULL;
p_array_t(p_chromosome_t) population = NULL;
p_array_t(p_chromosome_t) children = NULL;
p_chromosome_t elite = NULL;
bool *is_copyable = NULL;

/**
 * @private
 * @brief Compares the makespans of two specified chromosomes.
 * 
 * @param a Specified chromosome.
 * @param b Specified chromosome.
 * @return int Result.
 */
int compare_chromosome_makespan(const void *a, const void *b);
/**
 * @private
 * @brief Shuffles the genes of the specified chromosome. 
 * 
 * @param chromosome Specified chromosome.
 */
void shuffle(p_chromosome_t chromosome);
/**
 * @private
 * @brief Initializes the population.
 * 
 */
void initialize_population();
/**
 * @private
 * @brief Obtains a new chromosome, with genes shuffled randomly.
 * 
 */
p_chromosome_t get_random_chromosome();
/**
 * @private
 * @brief GOX Crossing Operator.
 * 
 * @param father Father chromosome.
 * @param mother Mother chromosome.
 */
p_chromosome_t GOX(p_chromosome_t father, p_chromosome_t mother);



int compare_chromosome_makespan(const void *a, const void *b) {
    assert((*(p_chromosome_t *)a)->makespan != MAKESPAN_UNCALCULATED);
    assert((*(p_chromosome_t *)b)->makespan != MAKESPAN_UNCALCULATED);
    return -(*(p_chromosome_t *)b)->makespan + (*(p_chromosome_t *)a)->makespan;
}

void shuffle(p_chromosome_t chromosome) {
    int j = 0;
    for (size_t i = chromosome->size - 1; i != 0; i--) {
        j = uniform_int_distribution(0, i);
        swap_int(&(chromosome->genes[i]), &(chromosome->genes[j]));
    }
    chromosome->makespan = MAKESPAN_UNCALCULATED;
}

void initialize_genetic_optimizer(int density, double rate) {
    population_density = density;
    reproductive_rate = rate;
    is_copyable = (bool *)calloc(target_order->num_of_operations, sizeof(bool));
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
    elite = new_chromosome_copy_from(template_chromosome);
    elite->makespan = INT_MAX;
    initialize_population();
}

void destroy_genetic_optimizer() {
    delete_array(population);
    delete_array(children);
    assert(is_copyable != NULL);
    free(is_copyable);
    is_copyable = NULL;
    destroy_chromosome_pool();
}

void initialize_population() {
    population = new_array(p_chromosome_t, population_density * 2);
    children = new_array(p_chromosome_t, population_density);
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
    size_t i = uniform_int_distribution(0, mother->size - 1);
    size_t j = uniform_int_distribution(0, mother->size - 1);
    while (i == j) {
        i = uniform_int_distribution(0, mother->size - 1);
        j = uniform_int_distribution(0, mother->size - 1);
    }
    size_t k = uniform_int_distribution(0, father->size);
    if (i > j) {
        swap_size_t(&i, &j);
    }
    makespan(father);
    makespan(mother);
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
    mutate(child);
    return child;
}

void evolve() {
    resize(children, 0);
    int indexA, indexB;
    for (int i = 0; i < population_density * reproductive_rate; i++) {
        indexA = abs(lround(normal_distribution(0, population_density / 1.5)));
        indexB = abs(lround(normal_distribution(0, population_density / 1.5)));
        if (indexA >= population_density) indexA = population_density - 1;
        if (indexB >= population_density) indexB = population_density - 1;
        push_back(children, GOX(population->data[indexA], population->data[indexB]));
    }
    for (size_t i = size(population) - size(children); i < size(population); i++) {
        delete_chromosome(population->data[i]);
    }
    resize(population, size(population) - size(children));
    memcpy(end(population), begin(children), size(children) * sizeof(p_chromosome_t));
    resize(population, population_density);
    for (size_t i = 0; i < size(population); i++) {
        makespan(population->data[i]);
    }
    qsort(begin(population), size(population), sizeof(front(population)), compare_chromosome_makespan);
    if (front(population)->makespan < elite->makespan) {
        delete_chromosome(elite);
        elite = new_chromosome_copy_from(front(population));
        target_order->makespan = elite->makespan;
    }
}

void genetic_optimize(int epoch) {
    target_order->makespan = INT_MAX;
    static int count = 0;
    int last_makespan = INT_MAX;

    while (epoch--) {
        if (target_order->makespan < last_makespan) {
            last_makespan = target_order->makespan;
            if (epoch < 1000000) {
                epoch = 1000000;
            }
        }
        if (count % 50000 == 0) {
            for (p_chromosome_t *i = begin(population); i != end(population); i++) {
                shuffle(*i);
            }
        }
#ifdef _DEBUG
        if (count % 10000 == 0) {
            printf("%d\n", target_order->makespan);
        }
#endif
        if (population->data[0]->makespan == population->data[4]->makespan) {
            for (size_t i = 0; i < size(population) / 2; i++) {
                mutate(population->data[i]);
                mutate(population->data[i]);
                mutate(population->data[i]);
                mutate(population->data[i]);
                mutate(population->data[i]);
                mutate(population->data[i]);
                mutate(population->data[i]);
                mutate(population->data[i]);
                mutate(population->data[i]);
                mutate(population->data[i]);
                makespan(population->data[i]);
            }
        }
        evolve();
        count++;
    }
    decode(elite);   
}
