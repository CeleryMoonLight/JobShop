#include "file.h"
#include <stdio.h>

order_t *new_order() {
	order_t *order = (order_t*)malloc(sizeof(order_t));
	if (order == NULL) {   /*�����̬����ռ�ʧ��*/
		return NULL;
	}		
	return order;
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

void read_from_console(order_t *test_order) {
	char ch;
	int i;                 /*ѭ������*/
	int a;
	scanf("%d", &(test_order->num_of_jobs));       /*�����Ʒ����*/
	scanf("%d", &(test_order->num_of_machines));  /*���������Ŀ*/
	test_order->operations = (operation_t**)malloc(sizeof(operation_t*) * test_order->num_of_jobs);  //Ϊָ�����鶯̬����ռ� 
	for (i = 0; i < test_order->num_of_jobs; i++) {
		test_order->operations[i] = (operation_t*)malloc(sizeof(operation_t) * 10);  //Ϊ�����е�Ԫ�ط���ռ� 
		if (test_order->operations[i] == NULL) {
			printf("����ʧ��\n");
		}
	}
	for (i = 0; i < test_order->num_of_jobs; i++) {
		a = 0;
		int b;
		scanf("%d", &b);
		ch = getchar();
		while (1) {
			if (ch == '(') {
				(test_order->operations[i][a]).period = change_from_char_to_num(getchar());
				(test_order->operations[i][a]).machine = change_from_char_to_num(getchar());
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
	int index;                 /*ѭ������*/
	int num_of_precedure;
	input_order->num_of_jobs = file_change_from_char_to_num(fp);       /*�����Ʒ����*/
	input_order->num_of_machines = file_change_from_char_to_num(fp);  /*���������Ŀ*/
	input_order->operations = (operation_t**)malloc(sizeof(operation_t*) * input_order->num_of_jobs);  //Ϊָ�����鶯̬����ռ� 
	for (index = 0; index <input_order->num_of_jobs; index++) {
		input_order->operations[index] = (operation_t*)malloc(sizeof(operation_t) * 10);  //Ϊ�����е�Ԫ�ط���ռ� 
		if (input_order->operations[index] == NULL) {
			printf("����ʧ��\n");
		}
	}
	for (index = 0; index < input_order->num_of_jobs; index++) {
		num_of_precedure = 0;
		(input_order->operations[index][num_of_precedure]).job = file_change_from_char_to_num(fp);   //��Ʒ��� 
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

void delete_order(order_t *test_order)
{
	for (int i = 0; i < test_order->num_of_jobs; i++) {
		free(test_order->operations[i]);
	}
	free(test_order);
}