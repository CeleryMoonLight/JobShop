/**
 * @brief 定义控制台程序入口点。
 * 
 * @file main.c
 * @author Jason Qiu
 * @date 2018-05-02
 */

#include "file.h"
#include "util.h"
#include "optimizer.h"

p_order_t target_order = NULL;

/**
 * @brief 定义控制台程序入口点。
 * 
 * @return int 程序运行无错误返回 0，否则返回非 0 值。
 */

int main(int argc, char *argv[]) {
    target_order = new_order();
    read_from_file(target_order, "./input.txt");
    initialize_random_engine();
    initialize_genetic_optimizer(300, 0.5);
    genetic_optimize();
    write_to_console(target_order);
    destroy_genetic_optimizer();
    delete_order(target_order);
    return 0;
}