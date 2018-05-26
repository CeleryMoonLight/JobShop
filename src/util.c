/**
 * @brief Implementation of util.h
 * 
 * @file util.c
 * @author Jason Qiu
 * @date 2018-05-25
 */
#include "util.h"

#include "base.h"
#include <math.h>

void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_size_t(size_t *a, size_t *b) {
    size_t temp = *a;
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
    const double PI = 3.1415926535;
    static double U, V;
    static int phase = 0;
    double z;
    if (phase == 0)
    {
        U = rand() / (RAND_MAX + 1.0);
        V = rand() / (RAND_MAX + 1.0);
        z = sqrt(-2.0 * log(U))* sin(2.0 * PI * V);
    }
    else
    {
        z = sqrt(-2.0 * log(U)) * cos(2.0 * PI * V);
    }

    phase = 1 - phase;
    return mean + z * stddev;
}
