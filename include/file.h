/**
 * @brief I/O-related functions.
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
 * @brief Reads the order information from a file.
 * 
 * @param input_order Order in which the information will be stored.
 * @param path File path.
 */
void read_from_file(p_order_t input_order, const char *path);

/**
 * @public
 * @brief Reads the order information from the console.
 * 
 * @param input_order Order in which the information will be stored.
 */
void read_from_console(p_order_t input_order);

/**
 * @public
 * @brief Writes the schedule of the specified order to a file.
 * 
 * @param output_order Specified order.
 * @param path File path.
 */
void write_to_file(p_order_t output_order, const char *path);

/**
 * @public
 * @brief Writes the schedule to the console.
 * 
 * @param output_order Specified order.
 */
void write_to_console(p_order_t output_order);

#endif // !_FILE_H_
