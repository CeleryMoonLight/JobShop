/**
 * @brief 宏实现的数组模板。
 * 
 * @file array.h
 * @author Jason Qiu
 * @date 2018-05-24
 */
#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief 从给定类型生成对应的 array_t 类型。
 * 
 * @param type 给定类型。
 */
#define define_array(type)\
\
struct _array_##type##_t;\
\
typedef struct {\
    bool (*is_empty)(const struct _array_##type##_t *);\
    size_t (*size)(const struct _array_##type##_t *);\
    type (*front)(const struct _array_##type##_t *);\
    type (*back)(const struct _array_##type##_t *);\
    type *(*begin)(const struct _array_##type##_t *);\
    type *(*end)(const struct _array_##type##_t *);\
    void (*pop_back)(struct _array_##type##_t *);\
    void (*push_back)(struct _array_##type##_t *, type);\
    void (*resize)(struct _array_##type##_t *, size_t);\
} array_vtable_##type##_t;\
\
typedef struct _array_##type##_t {\
    type *data;\
    type *begin;\
    type *end;\
    size_t capacity;\
    size_t size;\
    array_vtable_##type##_t *vtable;\
} array_##type##_t;\
\
typedef array_##type##_t *p_array_##type##_t;\
\
p_array_##type##_t new_array_##type(const int capacity);\
bool array_is_empty_##type(const struct _array_##type##_t *array);\
size_t array_size_##type(const struct _array_##type##_t *array);\
type array_front_##type(const struct _array_##type##_t *array);\
type array_back_##type(const struct _array_##type##_t *array);\
type *array_begin_##type(const struct _array_##type##_t *array);\
type *array_end_##type(const struct _array_##type##_t *array);\
void array_pop_back_##type(struct _array_##type##_t *array);\
void array_push_back_##type(struct _array_##type##_t *array, type element);\
void array_resize_##type(struct _array_##type##_t *array, size_t size);\
\
bool array_is_empty_##type(const struct _array_##type##_t *array) {\
    return array->size == 0;\
}\
\
size_t array_size_##type(const struct _array_##type##_t *array) {\
    return array->size;\
}\
\
type array_front_##type(const struct _array_##type##_t *array) {\
    return *(array->begin);\
}\
\
type array_back_##type(const struct _array_##type##_t *array) {\
    return *(array->end - 1);\
}\
type array_begin_##type(const struct _array_##type##_t *array) {\
    return array->begin;\
}\
type array_end_##type(const struct _array_##type##_t *array) {\
    return array->end;\
}\
void array_pop_back_##type(struct _array_##type##_t *array) {\
    array->end--;\
    array->size--;\
}\
\
void array_push_back_##type(struct _array_##type##_t *array, type element) {\
    *(array->end) = element;\
    array->end++;\
    array->size++;\
}\
void array_resize_##type(struct _array_##type##_t *array, size_t size) {\
    array->size = size;\
    array->end = array->begin + array->size;\
}\
\
array_vtable_##type##_t array_vtable_##type = {\
    &array_is_empty_##type,\
    &array_size_##type,\
    &array_front_##type,\
    &array_back_##type,\
    &array_begin_##type,\
    &array_end_##type,\
    &array_pop_back_##type,\
    &array_push_back_##type,\
    &array_resize_##type\
};\
\
p_array_##type##_t new_array_##type(const int capacity) {\
    p_array_##type##_t res = (p_array_##type##_t)malloc(sizeof(array_##type##_t));\
    res->data = (type *)malloc(sizeof(type) * capacity);\
    res->begin = res->data; \
    res->end = res->data;   \
    res->capacity = capacity;\
    res->size = 0;\
    res->vtable = &array_vtable_##type;\
    return res;\
}

#endif // !_ARRAY_H_