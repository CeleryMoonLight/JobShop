#ifndef _UTIL_H_
#define _UTIL_H_

/**
 * @brief 返回指定容器是否为空。
 * 
 * @param pointer 指定容器。
 * @return true 容器为空。
 * @return false 容器不为空。
 */
#define is_empty(pointer)\
    pointer->vtable->is_empty(pointer)
/**
 * @brief 返回指定容器的当前大小。
 * 
 * @param pointer 指定容器。
 * @return 当前容器大小。
 */
#define size(pointer)\
    pointer->vtable->size(pointer)
/**
 * @brief 返回指定容器的首元素。
 * 
 * @param pointer 指定容器。
 * @return 首元素。
 */
#define front(pointer)\
    pointer->vtable->front(pointer)
/**
 * @brief 返回指定容器的尾元素。
 * 
 * @param pointer 指定容器。
 * @return 尾元素。
 */
#define back(pointer)\
    pointer->vtable->back(pointer)
/**
 * @brief 指定容器队首出队一个元素。
 * 
 * @param pointer 指定容器。
 */

#define begin(pointer)\
    pointer->vtable->begin(pointer)

#define end(pointer)\
    pointer->vtable->end(pointer)  
    
#define pop(pointer)\
    pointer->vtable->pop(pointer)
/**
 * @brief 指定容器队尾入队一个元素。
 * 
 * @param pointer 指定容器。
 * @param element 要入队的元素。
 */
#define push(pointer, element)\
    pointer->vtable->push(pointer, element)

#define pop_back(pointer)\
    pointer->vtable->pop_back(pointer)

#define push_back(pointer, element)\
    pointer->vtable->push_back(pointer, element)

#define resize(pointer, size)\
    pointer->vtable->resize(pointer, size)

#endif // !_UTIL_H_