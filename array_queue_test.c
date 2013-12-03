//
//  array_queue_test.c
//  c-based-array-queue
//
//  Created by Blake Caldwell on 12/3/13.
//  Copyright (c) 2013 Blake Caldwell. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include "array_queue.h"

void assert_queue_equals(struct array_queue *queue, int head, int tail, int queue_size, int array_size, int array[]);

// test adding to, and removing from the queue, with queue expansion
void test_array_queue()
{
    struct array_queue *queue;
    int value;
    
    // try initializing queue with invalid size
    assert(!init_queue(5, &queue));
    assert(!queue);
    
    // initialize the queue with size 4
    assert(init_queue(4, &queue));
    assert_queue_equals(queue, 0, -1, 0, 4, (int[]){-100, -100, -100, -100 });
    
    // add 1
    assert(add_to_queue(queue, 1));
    assert_queue_equals(queue, 0, 0, 1, 4, (int[]){1, -100, -100, -100 });
    
    // add 2
    assert(add_to_queue(queue, 2));
    assert_queue_equals(queue, 0, 1, 2, 4, (int[]){1, 2, -100, -100 });
    
    // add 3
    assert(add_to_queue(queue, 3));
    assert_queue_equals(queue, 0, 2, 3, 4, (int[]){1, 2, 3, -100});
    
    // read 1
    assert(read_from_queue(queue, &value));
    assert(value == 1);
    assert_queue_equals(queue, 1, 2, 2, 4, (int[]){-100, 2, 3, -100});
    
    // add 4
    assert(add_to_queue(queue, 4));
    assert_queue_equals(queue, 1, 3, 3, 4, (int[]){-100, 2, 3, 4});
    
    // add 5
    assert(add_to_queue(queue, 5));
    assert_queue_equals(queue, 1, 0, 4, 4, (int[]){5, 2, 3, 4});
    
    // add 6 - queue grows
    assert(add_to_queue(queue, 6));
    assert_queue_equals(queue, 0, 4, 5, 8, (int[]){2, 3, 4, 5, 6, -100, -100, -100});
    
    // add 7 - queue grows
    assert(add_to_queue(queue, 7));
    assert_queue_equals(queue, 0, 5, 6, 8, (int[]){2, 3, 4, 5, 6, 7, -100, -100});
    
    // read 2
    assert(read_from_queue(queue, &value));
    assert(value == 2);
    assert_queue_equals(queue, 1, 5, 5, 8, (int[]){-100, 3, 4, 5, 6, 7, -100, -100});
    
    // read 3
    assert(read_from_queue(queue, &value));
    assert(value == 3);
    assert_queue_equals(queue, 2, 5, 4, 8, (int[]){-100, -100, 4, 5, 6, 7, -100, -100});
    
    // read 4
    assert(read_from_queue(queue, &value));
    assert(value == 4);
    assert_queue_equals(queue, 3, 5, 3, 8, (int[]){-100, -100, -100, 5, 6, 7, -100, -100});
    
    // read 5
    assert(read_from_queue(queue, &value));
    assert(value == 5);
    assert_queue_equals(queue, 4, 5, 2, 8, (int[]){-100, -100, -100, -100, 6, 7, -100, -100});
    
    // read 6
    assert(read_from_queue(queue, &value));
    assert(value == 6);
    assert_queue_equals(queue, 5, 5, 1, 8, (int[]){-100, -100, -100, -100, -100, 7, -100, -100});
    
    // read 7 - queue is empty
    assert(read_from_queue(queue, &value));
    assert(value == 7);
    assert_queue_equals(queue, 6, 5, 0, 8, (int[]){-100, -100, -100, -100, -100, -100, -100, -100 });
    
    // read again - empty queue
    assert(!read_from_queue(queue, &value));
    assert_queue_equals(queue, 6, 5, 0, 8, (int[]){-100, -100, -100, -100, -100, -100, -100, -100 });
    
    // start over, showing how the queue cleans itself up
    assert(add_to_queue(queue, 8));
    assert_queue_equals(queue, 6, 6, 1, 8, (int[]){-100, -100, -100, -100, -100, -100, 8, -100});
    
    // clean up
    destroy_queue(&queue);
    
    printf("-----------------------\n");
    printf("Array Queue Tests Pass!\n");
    printf("-----------------------\n");
}

// assert the queue looks as we expect
void assert_queue_equals(struct array_queue *queue, int head, int tail, int queue_size, int array_size, int array[])
{
    assert(queue->head == head);
    assert(queue->tail == tail);
    assert(queue->queue_size == queue_size);
    assert(queue->array_size == array_size);
    for(int i=0; i<array_size; i++)
    {
        if(array[i] != -100)    // ignore -100 - that's our dummy placeholder
        {
            assert(queue->array[i] == array[i]);
        }
    }
}