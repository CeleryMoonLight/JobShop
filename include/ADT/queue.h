/**
 * @brief Queue template implemented by marcos.
 * 
 * @file queue.h
 * @author Jason Qiu
 * @date 2018-05-18
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "../base.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Generates queue_t(type) of the specified type.
 * 
 * @param type Specified type.
 */
#define define_queue(type)\
\
struct _queue_##type##_t;\
\
typedef struct {\
    bool (*is_empty)(const struct _queue_##type##_t *);\
    size_t (*size)(const struct _queue_##type##_t *);\
    type (*front)(const struct _queue_##type##_t *);\
    void (*pop)(struct _queue_##type##_t *);\
    void (*push)(struct _queue_##type##_t *, type);\
} queue_vtable_##type##_t;\
\
typedef struct _queue_##type##_t {\
    type *data;\
    type *begin;\
    type *end;\
    size_t capacity;\
    size_t size;\
    queue_vtable_##type##_t *vtable;\
} queue_##type##_t;\
\
typedef queue_##type##_t *p_queue_##type##_t;\
\
p_queue_##type##_t new_queue_##type(const int capacity);\
bool queue_is_empty_##type(const struct _queue_##type##_t *queue);\
size_t queue_size_##type(const struct _queue_##type##_t *queue);\
type queue_front_##type(const struct _queue_##type##_t *queue);\
void queue_pop_##type(struct _queue_##type##_t *queue);\
void queue_push_##type(struct _queue_##type##_t *queue, type element);\
\
bool queue_is_empty_##type(const struct _queue_##type##_t *queue) {\
    return queue->size == 0;\
}\
\
size_t queue_size_##type(const struct _queue_##type##_t *queue) {\
    return queue->size;\
}\
\
type queue_front_##type(const struct _queue_##type##_t *queue) {\
    return *(queue->begin);\
}\
\
void queue_pop_##type(struct _queue_##type##_t *queue) {\
    if (queue->begin != queue->data + queue->capacity) {\
        queue->begin++;\
    } else {\
        queue->begin = queue->data;\
    }\
    queue->size--;\
}\
\
void queue_push_##type(struct _queue_##type##_t *queue, type element) {\
    *(queue->end) = element;\
    if (queue->end != queue->data + queue->capacity) {\
        queue->end++;\
    } else {\
        queue->end = queue->data;\
    }\
    queue->size++;\
}\
\
queue_vtable_##type##_t queue_vtable_##type = {\
    &queue_is_empty_##type,\
    &queue_size_##type,\
    &queue_front_##type,\
    &queue_pop_##type,\
    &queue_push_##type\
};\
\
p_queue_##type##_t new_queue_##type(const int capacity) {\
    p_queue_##type##_t res = NULL;\
    res = (p_queue_##type##_t)calloc(1, sizeof(queue_##type##_t));\
    res->data = (type *)calloc(capacity, sizeof(type));\
    res->begin = res->data; \
    res->end = res->data;   \
    res->capacity = capacity;\
    res->size = 0;\
    res->vtable = &queue_vtable_##type;\
    return res;\
}

#define p_queue_t(type) \
    p_queue_##type##_t
 /**
 * @brief Constructs queue_t(type).
 *
 * @param type Specified type.
 * @param capacity Max capacity.
 * @sa p_queue_t, delete_queue
 */
#define new_queue(type, capacity)\
    new_queue_##type(capacity)
 /**
 * @brief Destroys the specified queue.
 *
 * @param pointer Specified queue.
 * @sa new_queue
 */
#define delete_queue(pointer)\
    {\
        assert(pointer != NULL);\
        assert(pointer->data != NULL);\
        free(pointer->data);\
        free(pointer);\
    }

#endif // !_QUEUE_H_
