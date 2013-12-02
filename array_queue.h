//
//  Array-backed integer FIFO queue
//
//  Created by Blake Caldwell on 12/1/13.
//  Copyright (c) 2013 Blake Caldwell. All rights reserved.
//
//  Initialize a queue with a specified size. We insert items at the tail
//  of the queue, read from the head. Here's what the array looks like after
//  inserting 1, 2, 3 in an array with size 5. -100 is used to illustrated
//  unused values
//  [1 (head) (tail), -100, -100, -100, -100]
//  [1 (head), 2 (tail), -100, -100, -100]
//  [1 (head), 2, 3 (tail), -100, -100]
//
//  When we read a value, we start with 1:
//
//  [-100, 2 (head), 3 (tail), -100, -100]
//
//  We than add 4, 5, 6 and have this:
//  [-100, 2 (head), 3, 4 (tail), -100]
//  [-100, 2 (head), 3, 4, 5 (tail)]
//  [6(tail), 2 (head), 3, 4, 5]
//
//  Note that tail is now behind head, and we're out of room. Our next insert
//  of 7 doubles the array size, and cleans up the ordering:
//
//  [2(head), 3, 4, 5, 6, 7(tail), -100, -100, -100, -100]
//
//  Then read a few more times until it's empty:
//  [-100, 3(head), 4, 5, 6, 7 (tail), -100, -100, -100, -100]
//  [-100, -100, 4(head), 5, 6, 7 (tail), -100, -100, -100, -100]
//  [-100, -100, -100, 5(head), 6, 7 (tail), -100, -100, -100, -100]
//  [-100, -100, -100, -100, 6 (head), 7 (tail), -100, -100, -100, -100]
//  [-100, -100, -100, -100, -100, 7 (head) (tail), -100, -100, -100, -100]
//  [-100, -100, -100, -100, -100, -100 (head) (tail), -100, -100, -100, -100]
//
//  Then add 8 to show the queue cleaning itself up
//  [8 (head) (tail), -100, -100, -100, -100, -100, -100, -100, -100, -100]
//

#ifndef Practice_array_queue_h
#define Practice_array_queue_h

// [head, 1, 2, 3, 4, tail]
struct array_queue
{
    int head;       // we pop from head - beginning of array
    int tail;       // we push to tail - end of array
    int queue_size;
    int array_size;
    int *array;
};

// initialize a queue - return 0 on failure
int init_queue(int size, struct array_queue **queue);

// destroy the queue - return 0 on failure
int destroy_queue(struct array_queue **queue);

// add to queue - return 0 on failure
int add_to_queue(struct array_queue *queue, int value);

// read from the queue, removing the value
int read_from_queue(struct array_queue *queue, int *value);

#endif
