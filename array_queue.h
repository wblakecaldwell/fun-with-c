//
//  Array-backed integer FIFO queue
//
//  Created by Blake Caldwell on 12/1/13.
//  Copyright (c) 2013 Blake Caldwell. All rights reserved.
//

#ifndef Practice_array_queue_h
#define Practice_array_queue_h

// [head, 1, 2, tail]
struct array_queue
{
    int head;       // we pop from head - beginning of array
    int tail;       // we push to tail - end of array
    int queue_size;
    int array_size; // must be a power of 2
    int *array;
};

// initialize a queue with the given size (must be a power of 2) - return 0 on failure
int init_queue(unsigned int size, struct array_queue **queue);

// destroy the queue - return 0 on failure
int destroy_queue(struct array_queue **queue);

// add to queue - return 0 on failure
int add_to_queue(struct array_queue *queue, int value);

// read from the queue, removing the value
int read_from_queue(struct array_queue *queue, int *value);

#endif
