//
//  Array-backed integer FIFO queue: Implementation
//
//  See header for info
//

#include <stdio.h>
#include <stdlib.h>
#include "array_queue.h"

// enable debug info
#define SHOW_DEBUG 1

void print_queue(struct array_queue *queue);

// initialize a queue - return 0 on failure
int init_queue(int size, struct array_queue **queue)
{
#ifdef SHOW_DEBUG
    printf("Creating queue with initial length of %i\n", size);
#endif
    
    struct array_queue *new_queue = malloc(sizeof(struct array_queue));
    new_queue->array_size = size;
    new_queue->array = malloc(sizeof(int) * size);
    new_queue->queue_size = 0;
    new_queue->head = 0;
    new_queue->tail = 0;
    *queue = new_queue;
    
#ifdef SHOW_DEBUG
    for(int i=0; i<new_queue->array_size; i++)
    {
        new_queue->array[i] = -100;
    }
#endif
    
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
    
#ifdef SHOW_DEBUG
    printf("Destroyed queue\n");
#endif
    return 1;
}

// add to queue - return 0 on failure
int add_to_queue(struct array_queue *queue, int value)
{
#ifdef SHOW_DEBUG
    printf("Adding %i to queue\n", value);
#endif
    
    // determine the new head
    if(0 == queue->queue_size)
    {
        // empty queue
        queue->head = queue->tail = 0;
        queue->array[0] = value;
    }
    else if(queue->queue_size == queue->array_size)
    {
        // need more space
#ifdef SHOW_DEBUG
        printf("Need more space - doubling queue to %i\n", queue->array_size * 2);
#endif
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
            // [0,tail,NULL,NULL,head,5]
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
        
#ifdef SHOW_DEBUG
        for(int i=queue->tail+1; i<queue->array_size; i++)
        {
            queue->array[i] = -100;
        }
#endif
        
        // queue size didn't change
    }
    else if(queue->tail == (queue->array_size - 1))
    {
        // we have enough space, but tail is at the end of array
        queue->tail = 0;
        queue->array[queue->tail] = value;
    }
    else
    {
        // we have enough room, and tail is before end of array - simplest case
        queue->tail++;
        queue->array[queue->tail] = value;
    }
    
    queue->queue_size ++;
    
#ifdef SHOW_DEBUG
    print_queue(queue);
#endif
    
    return 1;
}

// read from the queue, removing the value
// return 0 if no item found
int read_from_queue(struct array_queue *queue, int *value)
{
    if(0 == queue->queue_size)
    {
        // nothing in queue
#ifdef SHOW_DEBUG
        printf("Read from queue - queue is empty\n");
        print_queue(queue);
#endif
        return 0;
    }
    int old_head = queue->head;
    *value = queue->array[queue->head];
    
    if(queue->queue_size > 1)
    {
        queue->head++;
    }
    if(queue->head >= queue->array_size)
    {
        queue->head = 0;
    }
    queue->queue_size--;
    
#ifdef SHOW_DEBUG
    queue->array[old_head] = -100;
    printf("Read %i from queue\n", *value);
    print_queue(queue);
#endif
    
    return 1;
}

// print the queue for debugging 
void print_queue(struct array_queue *queue)
{
    int size = queue->array_size;
    int *array = queue->array;
    printf("[");
    for(int i=0; i<size; i++)
    {
        if(i>0)
        {
            printf(",");
        }
        printf("%i", array[i]);
        
        if(queue->head == i)
        {
            printf(" (head)");
        }
        
        if(queue->tail == i)
        {
            printf(" (tail)");
        }
    }
    printf("]\n\n");
}

