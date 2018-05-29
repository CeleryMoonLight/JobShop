/**
 * @brief Defines the entry point for the console application.
 * 
 * @file main.c
 * @author Jason Qiu
 * @date 2018-05-02
 */

#include "file.h"
#include "util.h"
#include "optimizer.h"
#include <stdio.h>

p_order_t target_order = NULL;

/**
 * @brief Defines the entry point for the console application.
 * 
 */

int main(int argc, char *argv[]) {
    target_order = new_order();
    read_from_console(target_order);
    clock_t start_time = clock();
    initialize_random_engine();
    initialize_genetic_optimizer(5, 0.2);
    genetic_optimize(4000000);
    write_to_console(target_order);
    printf("Time Used: %.3lfs\n", (clock() - start_time) / 1000.0);
    printf("End Time: %d\n", target_order->makespan);
 //   destroy_genetic_optimizer();
 //   delete_order(target_order);
    return 0;
}