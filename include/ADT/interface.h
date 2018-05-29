/**
 * @brief Interfaces of the containers.
 * 
 * @file interface.h
 * @author Jason Qiu
 * @date 2018-05-25
 */
#ifndef _INTERFACE_H_
#define _INTERFACE_H_

/**
 * @brief Returns whether the specified container is empty.
 * 
 * @param container Specified container.
 * @return true The container is empty.
 * @return false The container is not empty.
 */
#define is_empty(container)\
    container->vtable->is_empty(container)
/**
 * @brief Returns the size of the specified container.
 * 
 * @param container Specified container.
 * @return Size of the pecified container.
 */
#define size(container)\
    container->vtable->size(container)
/**
 * @brief Returns the first element of the pecified container.
 * 
 * @param container Specified container.
 * @return First element.
 */
#define front(container)\
    container->vtable->front(container)
/**
 * @brief Returns the last element of the pecified container.
 * 
 * @param container Specified container.
 * @return Last element.
 */
#define back(container)\
    container->vtable->back(container)

 /**
 * @brief Returns the begin iterator of the spceified container.
 *
 * @param container Specified container.
 */
#define begin(container)\
    container->vtable->begin(container)
 /**
 * @brief Returns the end iterator of the spceified container.
 *
 * @param container Specified container.
 */
#define end(container)\
    container->vtable->end(container)  

#define pop(container)\
    container->vtable->pop(container)

#define push(container, element)\
    container->vtable->push(container, element)

#define pop_back(container)\
    container->vtable->pop_back(container)

#define push_back(container, element)\
    container->vtable->push_back(container, element)

#define resize(container, size)\
    container->vtable->resize(container, size)

#endif // !_INTERFACE_H_
