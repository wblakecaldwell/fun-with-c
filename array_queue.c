//
//  Array-backed integer FIFO queue: Implementation
//
//

#include <stdio.h>
#include <stdlib.h>
#include "array_queue.h"

// Note: I didn't write this method - copied and pasted :)
// make sure the input value is a power of 2
int is_power_of_two (unsigned int x)
{
    while (((x % 2) == 0) && x > 1) /* While x is even and > 1 */
    {
        x /= 2;
    }
    return (x == 1);
}

// initialize a queue - return 0 on failure
int init_queue(unsigned int size, struct array_queue **queue)
{
    if(!is_power_of_two(size))
    {
        // queue size must be power of 2
        *queue = NULL;
        return 0;
    }
    
    struct array_queue *new_queue = malloc(sizeof(struct array_queue));
    new_queue->array_size = size;
    new_queue->array = malloc(sizeof(int) * size);
    new_queue->queue_size = 0;
    new_queue->head = 0;
    new_queue->tail = -1;       // starts at -1 to make add logic easier - always allowed to increment this
    *queue = new_queue;
    return 1;
}

// destroy the queue - return 0 on failure
int destroy_queue(struct array_queue **queue)
{
    if(*queue != NULL)
    {
        free((*queue)->array);
        free(*queue);
        *queue = NULL;
    }
    return 1;
}

// add to queue - return 0 on failure
int add_to_queue(struct array_queue *queue, int value)
{
    // determine the new head
    if(queue->queue_size == queue->array_size)
    {
        // need more space
        int index = 0;
        
        int *new_queue = malloc(sizeof(int) * queue->array_size * 2);
        
        // copy over existing queue - from tail to head
        if(queue->tail >= queue->head)
        {
            for(int i = queue->head; i <= queue->tail; i++, index++)
            {
                new_queue[index] = queue->array[i];
            }
        }
        else
        {
            // tail is before head:
            // [0,tail,NULL,NULL,NULL,NULL,head,5]
            for(int i = queue->head; i < queue->array_size; i++, index++)
            {
                new_queue[index] = queue->array[i];
            }
            for(int i = 0; i <= queue->tail; i++, index++)
            {
                new_queue[index] = queue->array[i];
            }
        }
        free(queue->array);
        queue->array = new_queue;
        
        queue->tail = queue->queue_size;    // old queue size
        queue->head = 0;
        queue->array_size = queue->array_size * 2;
        queue->array[queue->tail] = value;
        
        // queue size didn't change
    }
    else
    {
        // we have enough space, but tail is at the end of array
        queue->tail ++;
        
        // with queue size being a power of 2, we can increment, then mask to loop back to index 0 if needed
        queue->tail &= (queue->array_size - 1);
        queue->array[queue->tail] = value;
    }
    
    queue->queue_size ++;
    return 1;
}

// read from the queue, removing the value
// return 0 if no item found
int read_from_queue(struct array_queue *queue, int *value)
{
    if(0 == queue->queue_size)
    {
        // nothing in queue
        return 0;
    }
    *value = queue->array[queue->head++];
    
    // with queue size being a power of 2, we can increment, then mask to loop back to index 0 if needed
    queue->head &= (queue->array_size - 1);
    queue->queue_size--;
    
    return 1;
}

