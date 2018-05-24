/**
 * @brief 定义控制台程序入口点。
 * 
 * @file main.c
 * @author Jason Qiu
 * @date 2018-05-02
 */

#include <stdio.h>
#include "file.h"
#include "optimizer.h"

p_order_t target_order = NULL;

/**
 * @brief 定义控制台程序入口点。
 * 
 * @return int 程序运行无错误返回 0，否则返回非 0 值。
 */

int main(int argc, char *argv[]) {
    target_order = new_order();
    read_from_console(target_order);
    read_from_file(target_order, "./input.txt");    
    initialize_genetic_optimizer(0, 0);
    genetic_optimize();
    write_to_console();
    write_to_file();
    destroy_genetic_optimizer();
    delete_order(target_order);
    return 0;
}