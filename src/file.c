/**
 * @brief Implementation of file.h
 * 
 * @file file.c
 * @author Celery Meng
 * @date 2018-05-03
 */

#include "file.h"
#include <stdio.h>

#define MAX_JOBS_SIZE 100

order_t *new_order() {
	return (order_t*)malloc(sizeof(order_t));
}

int change_from_char_to_num() {
	char ch;
	ch = getchar();
	int num = 0;
	while (ch >= '0' && ch <= '9') {
		num = num * 10 + (ch - '0');
		ch = getchar();
	}
	printf("%d ", num);
	return num;
}

void read_from_console(order_t *input_order) {
	char ch;
	int i;                 /*循环变量*/
	int a;
	scanf("%d", &(input_order->num_of_jobs));       /*输入产品参数*/
	scanf("%d", &(input_order->num_of_machines));  /*输入机器数目*/
	input_order->operations = (operation_t**)malloc(sizeof(operation_t*) * input_order->num_of_jobs);  //为指针数组动态分配空间 
	for (i = 0; i < input_order->num_of_jobs; i++) {
		input_order->operations[i] = (operation_t*)malloc(sizeof(operation_t) * MAX_JOBS_SIZE);  //为数组中的元素分配空间 
	}
	for (i = 0; i < input_order->num_of_jobs; i++) {
		a = 0;
		int b;
		scanf("%d", &b);
		ch = getchar();
		while (1) {
			if (ch == '(') {
				(input_order->operations[i][a]).period = change_from_char_to_num(getchar());
				(input_order->operations[i][a]).machine = change_from_char_to_num(getchar());
				a++;
				ch = getchar();
			}
			if (ch == '\n') {
				break;
			}
			ch = getchar();
		}
	}
}

void read_from_file(order_t *input_order, const char *path) {
	FILE *fp = fopen(path, "r");
	if (fp == NULL) {
		printf("Open files failed!\n");
	}
	rewind(fp);
	char ch;
	int index;                 /*循环变量*/
	int num_of_precedure;
	input_order->num_of_jobs = file_change_from_char_to_num(fp);       /*输入产品参数*/
	input_order->num_of_machines = file_change_from_char_to_num(fp);  /*输入机器数目*/
	input_order->operations = (operation_t**)malloc(sizeof(operation_t*) * input_order->num_of_jobs);  //为指针数组动态分配空间 
	for (index = 0; index <input_order->num_of_jobs; index++) {
		input_order->operations[index] = (operation_t*)malloc(sizeof(operation_t) * 10);  //为数组中的元素分配空间 
		if (input_order->operations[index] == NULL) {
			printf("分配失败\n");
		}
	}
	for (index = 0; index < input_order->num_of_jobs; index++) {
		num_of_precedure = 0;
		(input_order->operations[index][num_of_precedure]).job = file_change_from_char_to_num(fp);   //产品序号 
		ch = fgetc(fp);
		while (1) {
			if (ch == '(') {
				(input_order->operations[index][num_of_precedure]).period = file_change_from_char_to_num(fp);
				(input_order->operations[index][num_of_precedure]).machine = file_change_from_char_to_num(fp);
				num_of_precedure++;
				ch = fgetc(fp);
			}
			if (ch == '\n') {
				break;
			}
			ch = fgetc(fp);
		}
	}
	fclose(fp);
}

int file_change_from_char_to_num(FILE *fp) {
	char ch = fgetc(fp);
	int num = 0;
	while (ch >= '0' && ch <= '9') {
		num = num * 10 + (ch - '0');
		ch = fgetc(fp);
	}
	return num;
}

void delete_order(order_t *to_be_deleted)
{
	for (int i = 0; i < to_be_deleted->num_of_jobs; i++) {
		free(to_be_deleted->operations[i]);
	}
    free(to_be_deleted->operations);
	free(to_be_deleted);
}
