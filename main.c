//
//  main.c
//  Practice
//
//  Created by Blake Caldwell on 11/18/13.
//  Copyright (c) 2013 Blake Caldwell. All rights reserved.
//

#include <stdio.h>

#import "array_queue.h"

void demo_array_queue();

int main(int argc, const char * argv[])
{
    demo_array_queue();
    return 0;
}

// demo the array-based queue sample case as described in the header file
void demo_array_queue()
{
    struct array_queue *queue;
    int value;
    
    init_queue(5, &queue);
    add_to_queue(queue, 1);
    add_to_queue(queue, 2);
    add_to_queue(queue, 3);
    read_from_queue(queue, &value);         // read 1
    add_to_queue(queue, 4);
    add_to_queue(queue, 5);
    add_to_queue(queue, 6);
    add_to_queue(queue, 7);
    read_from_queue(queue, &value);         // read 2
    read_from_queue(queue, &value);         // read 3
    read_from_queue(queue, &value);         // read 4
    read_from_queue(queue, &value);         // read 5
    read_from_queue(queue, &value);         // read 6
    read_from_queue(queue, &value);         // read 7 - queue is empty
    read_from_queue(queue, &value);         // read one more to show it's empty
    
    // start over, showing how the queue cleans itself up
    add_to_queue(queue, 8);
    
    // clean up
    destroy_queue(&queue);
}
