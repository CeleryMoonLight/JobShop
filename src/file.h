/**
 * @brief 定义 I/O 相关操作。
 * 
 * @file file.h
 * @author Jason Qiu
 * @date 2018-05-02
 */

#ifndef _FILE_H_
#define _FILE_H_

#include "base.h"

/**
 * @brief 从文件中读入订单信息。
 * 
 * @param input_order 读入的订单信息所要存储的 order。
 * @param path 文件路径。
 * @author Celery Meng
 */
void read_from_file(
    OUT p_order_t input_order, 
    IN const char *path
);

/**
 * @brief 从控制台读入订单信息。
 * 
 * @param input_order 读入的订单信息所要存储的 order。
 * @author Celery Meng
 */
void read_from_console(
    OUT p_order_t input_order
);

void write_to_file();
void write_to_console();

#endif // !_FILE_H_
