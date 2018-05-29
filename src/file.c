/**
 * @brief Implementation of file.h.
 * 
 * @file file.c
 * @author Celery Meng, Jason Qiu
 * @date 2018-05-03
 */
#include "file.h"

#include <stdio.h>

#include "base.h"
#include "ADT/ADT.h"

#define MAX_JOBS_SIZE 128
#define BUFFER_SIZE 1024

define_array(operation_t);

/**
 * @private
 * @brief Movse the input pointer to the next number.
 * 
 * @param forward Input pointer.
 * @return true Moved successfully.
 * @return false Moved failed because there is no next number.
 */
bool next_digit(char **forward);
/**
 * @private
 * @brief Reads the order information from the spceified stream.
 * 
 * @param input_order Order.
 * @param stream Spceified input stream.
 */
void read(p_order_t input_order, FILE *stream);
/**
 * @private
 * @brief Writes the schedule to the spceified stream.
 * 
 * @param output_order Order.
 * @param stream Spceified output stream.
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
    for (size_t index_of_job = 0; index_of_job < input_order->num_of_jobs; index_of_job++) {
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

int compare_begin_time(const void *a, const void *b) {
    return ((p_operation_t)a)->begin_time - ((p_operation_t)b)->begin_time;
}

void write(p_order_t output_order, FILE *stream) {
    p_array_t(operation_t) *schedule_output = (p_array_t(operation_t) *)calloc(output_order->num_of_machines, sizeof(p_array_t(operation_t)));
    for (size_t i = 0; i < output_order->num_of_machines; i++) {
        schedule_output[i] = new_array(operation_t, output_order->num_of_jobs);
    }
    for (size_t i = 0; i < output_order->num_of_jobs; i++) {
        for (size_t j = 0; j < output_order->operations_of_jobs[i]; j++) {
            int machine = output_order->operations[i][j].machine;
            push_back(schedule_output[machine], output_order->operations[i][j]);
        }
    }
    for (size_t i = 0; i < output_order->num_of_machines; i++) {
        qsort(begin(schedule_output[i]), size(schedule_output[i]), sizeof(front(schedule_output[i])), compare_begin_time);
    }
    for (size_t i = 0; i < output_order->num_of_machines; i++) {
        fprintf(stream, "M%d", i);
        for (p_operation_t op = begin(schedule_output[i]); op != end(schedule_output[i]); op++) {
            fprintf(stream, " (%d, %d-%d, %d)", op->begin_time, op->job, op->index, op->end_time);
        }
        fputc('\n', stream);
        delete_array(schedule_output[i]);
    }
    free(schedule_output);
}