/**
 * @brief Implementation of file.h
 * 
 * @file file.c
 * @author Celery Meng
 * @date 2018-05-03
 */

#include "file.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_JOBS_SIZE 128
#define BUFFER_SIZE 1024
#define INPUT_STATE_NUM 0
#define INPUT_STATE_COMMA 1

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

void read(order_t *input_order, FILE *stream) {
    static char buffer[BUFFER_SIZE];
    fscanf(
        stream,
        "%d %d",
        &(input_order->num_of_jobs),
        &(input_order->num_of_machines)
    );
    input_order->operations = (operation_t **)
        calloc(
            input_order->num_of_jobs,
            sizeof(operation_t *)
        );
    for (int index = 0; index < input_order->num_of_jobs; index++) {
        input_order->operations[index] = (operation_t *)
            calloc(
                MAX_JOBS_SIZE,
                sizeof(operation_t)
            );
    }
    char *forward = NULL;
    bool is_ended = false;
    for (int index_of_job = 0; index_of_job < input_order->num_of_jobs; index_of_job++) {
        fscanf(stream, "%*d");
        fgets(buffer, BUFFER_SIZE, stream);
        forward = buffer;
        int index_of_operation = 0;
        while (true) {
            is_ended = next_digit(&forward);
            if (is_ended) {
                break;
            }
            sscanf(forward, "%d", &((input_order->operations[index_of_job][index_of_operation]).period));
            is_ended = next_digit(&forward);
            if (is_ended) {
                break;
            }
            sscanf(forward, "%d", &((input_order->operations[index_of_job][index_of_operation]).machine));
            input_order->operations[index_of_job][index_of_operation].job = index_of_job;
            index_of_operation++;
        }
    }
}

void read_from_console(order_t *input_order) {
    read(input_order, stdin);
}

void read_from_file(order_t *input_order, const char *path) {
    FILE *fp = fopen(path, "r");
    read(input_order, fp);
    fclose(fp);
}