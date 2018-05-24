/**
 * @brief 宏实现的队列模板。
 * 
 * @file queue.h
 * @author Jason Qiu
 * @date 2018-05-18
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief 从给定类型生成对应的 queue_t 类型。
 * 
 * @param type 给定类型。
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
    p_queue_##type##_t res = (p_queue_##type##_t)malloc(sizeof(queue_##type##_t));\
    res->data = (type *)malloc(sizeof(type) * capacity);\
    res->begin = res->data; \
    res->end = res->data;   \
    res->capacity = capacity;\
    res->size = 0;\
    res->vtable = &queue_vtable_##type;\
    return res;\
}

/**
 * @brief 指定类型的队列。
 * 
 * @param type 给定类型。
 * @sa new_queue
 */
#define p_queue_t(type) \
    queue_##type##_t *
/**
 * @brief 构造指定类型的队列。
 * 
 * @param type 给定类型。
 * @param capacity 队列容量。
 * @sa p_queue_t, delete_queue
 */
#define new_queue(type, capacity)\
    new_queue_##type(capacity)
/**
 * @brief 销毁指定的队列。
 * 
 * @param pointer 指定队列。
 * @sa new_queue
 */
#define delete_queue(pointer)\
    {\
        free(pointer->data);\
        free(pointer);\
    }
/**
 * @brief 返回指定队列是否为空。
 * 
 * @param pointer 指定队列。
 * @return true 队列为空。
 * @return false 队列不为空。
 */
#define is_empty(pointer)\
    pointer->vtable->is_empty(pointer)
/**
 * @brief 返回指定队列的当前大小。
 * 
 * @param pointer 指定队列。
 * @return 当前队列大小。
 */
#define size(pointer)\
    pointer->vtable->size(pointer)
/**
 * @brief 返回指定队列的队首元素。
 * 
 * @param pointer 指定队列。
 * @return 队首元素。
 */
#define front(pointer)\
    pointer->vtable->front(pointer)
/**
 * @brief 指定队列队首出队一个元素。
 * 
 * @param pointer 指定队列。
 */
#define pop(pointer)\
    pointer->vtable->pop(pointer)
/**
 * @brief 指定队列队尾入队一个元素。
 * 
 * @param pointer 指定队列。
 * @param element 要入队的元素。
 */
#define push(pointer, element)\
    pointer->vtable->push(pointer, element)

#endif // !_QUEUE_H_
