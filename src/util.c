/**
 * @brief Implementation of util.h
 * 
 * @file util.c
 * @author Jason Qiu
 * @date 2018-05-25
 */
#include "util.h"

#include "base.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void initialize_random_engine() {
    srand(time(NULL));
}

void initialize_random_engine_with_seed(unsigned int seed) {
    srand(seed);
}

int uniform_int_distribution(int lower_bound, int upper_bound) {
    return rand() % (upper_bound - lower_bound + 1) + lower_bound;
}

double normal_distribution(double mean, double stddev) {

}
