/**
 * @brief 此文件定义了 I/O 相关的操作。
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
 */
void read_from_file(
    OUT order *input_order, 
    IN const char *path
);

/**
 * @brief 从控制台读入订单信息。
 * 
 * @param input_order 读入的订单信息所要存储的 order。
 */
void read_from_console(
    OUT order *input_order
);

#endif // !_FILE_H_
