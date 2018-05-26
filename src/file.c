/**
 * @brief Implementation of file.h.
 * 
 * @file file.c
 * @author Celery Meng
 * @date 2018-05-03
 */
#include "file.h"

#include <stdio.h>

#include "base.h"

#define MAX_JOBS_SIZE 128
#define BUFFER_SIZE 1024

/**
 * @private
 * @brief 将给定读入指针移至下一个数字处。
 * 
 * @param forward 给定读入指针。
 * @return true 移动成功。
 * @return false 移动失败，已经没有下一个数字。
 */
bool next_digit(char **forward);
/**
 * @private
 * @brief 从给定流中读入订单信息。
 * 
 * @param input_order 要输入的订单。
 * @param stream 给定输入流。
 */
void read(p_order_t input_order, FILE *stream);
/**
 * @private
 * @brief 向给定流中输出订单规划信息。
 * 
 * @param output_order 要输出的订单。
 * @param stream 给定输出流。
 */
void write(p_order_t output_order, FILE *stream);

void read_from_file(p_order_t input_order, const char *path) {
    FILE *fp = fopen(path, "r");
    read(input_order, fp);
    fclose(fp);
}

void read_from_console(p_order_t input_order) {
    read(input_order, stdin);
}

void write_to_file(p_order_t output_order, const char *path) {
    FILE *fp = fopen(path, "w");
    write(output_order, fp);
    fclose(fp);
}

void write_to_console(p_order_t output_order) {
    write(output_order, stdout);
}

bool next_digit(char **forward) {
    while (**forward != '\0' && isdigit(**forward)) {
        (*forward)++;
    }
    while (**forward != '\0' && !isdigit(**forward)) {
        (*forward)++;
    }
    if (**forward == '\0') {
        return true;
    }
    else {
        return false;
    }
}

void read(p_order_t input_order, FILE *stream) {
    static char buffer[BUFFER_SIZE];
    fscanf(
        stream,
        "%zu %zu",
        &(input_order->num_of_jobs),
        &(input_order->num_of_machines)
    );
    input_order->operations = (p_operation_t *)
        calloc(
            input_order->num_of_jobs,
            sizeof(p_operation_t)
        );
    for (size_t index = 0; index < input_order->num_of_jobs; index++) {
        input_order->operations[index] = (p_operation_t)
            calloc(
                MAX_JOBS_SIZE,
                sizeof(operation_t)
            );
    }
    input_order->operations_of_jobs = (size_t *)
        calloc(
            input_order->num_of_jobs,
            sizeof(size_t)
        );

    char *forward = NULL;
    bool is_ended = false;
    buffer[0] = ' ';
    for (int index_of_job = 0; index_of_job < input_order->num_of_jobs; index_of_job++) {
        char line_head = '\0';
        while (!isgraph(line_head)) {
            line_head = fgetc(stream);
        }
        fgets(buffer + 2, BUFFER_SIZE - 2, stream);
        *(buffer + 1) = line_head;
        forward = buffer;
        int index_of_operation = 0;
        while (true) {
            is_ended = next_digit(&forward);
            if (is_ended) {
                break;
            }
            sscanf(forward, "%d", &((input_order->operations[index_of_job][index_of_operation]).machine));
            is_ended = next_digit(&forward);
            if (is_ended) {
                break;
            }
            sscanf(forward, "%d", &((input_order->operations[index_of_job][index_of_operation]).period));
            input_order->operations[index_of_job][index_of_operation].job = index_of_job;
            input_order->operations[index_of_job][index_of_operation].index = index_of_operation;
            input_order->operations_of_jobs[index_of_job]++;
            input_order->num_of_operations++;
            index_of_operation++;
        }
    }
}

void write(p_order_t output_order, FILE *stream) {

}