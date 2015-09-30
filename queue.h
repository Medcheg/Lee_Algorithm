#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

#define DEFAULT_QUEUE_SIZE 256

typedef struct tag_queue_value
{
    uint32_t x;
    uint32_t y;
    uint32_t  value;
}queue_value_t;

typedef struct tag_queue
{
    uint32_t queue_size;

    uint32_t tail_index;
    uint32_t head_index;

    queue_value_t *entries;
}queue_t;

/*
 * Function: void queue_initialise (Queue_t *queue)
 * Purpose : initialise a queue
 * Params  : queue - queue to initialise
 */
void queue_init( queue_t *queue);

/*
 * Function: void queue_free (Queue_t *queue)
 * Purpose : free a queue
 * Params  : queue - queue to free
 */
void queue_free( queue_t *queue);
void queue_push( queue_t *queue, queue_value_t push_value);

void queue_pop ( queue_t *queue, queue_value_t *pop_value);

#endif
