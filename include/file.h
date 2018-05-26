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
 * @public
 * @brief 从文件中读入订单信息。
 * 
 * @param input_order 读入的订单信息所要存储的订单。
 * @param path 文件路径。
 */
void read_from_file(p_order_t input_order, const char *path);

/**
 * @public
 * @brief 从控制台读入订单信息。
 * 
 * @param input_order 读入的订单信息所要存储的订单。
 */
void read_from_console(p_order_t input_order);

/**
 * @public
 * @brief 向文件中输出给定订单的工序规划。
 * 
 * @param output_order 给定订单。
 * @param path 文件路径。
 * @author Celery Meng
 */
void write_to_file(p_order_t output_order, const char *path);

/**
 * @public
 * @brief 向控制台中输出给定订单的工序规划。
 * 
 * @param output_order 给定订单。
 * @author Celery Meng
 */
void write_to_console(p_order_t output_order);

#endif // !_FILE_H_
