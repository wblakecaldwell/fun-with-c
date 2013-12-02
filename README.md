c-array-based-queue
===================

Simple (non-optimal) Array-backed integer FIFO queue in C. 

Note: This can be sped up by bitmasking head and tail with array_size-1. I plan on updating at some point.

Details
-------

Rather than use a linked list, this queue uses a fixed-size array for its storage. Initially, new values are written to the end of the array, values are read from the beginning. The array's head and tail indices are tracked to handle when the tail of the queue wraps around to the beginning of the array, or if we run out of room and need to double the array. 

Demo
----

Compile and run to see a demo run.

    gcc *.c -D SHOW_DEBUG
    ./a.out

The demo performs the following:

Initialize a queue with size 5, then insert 1, 2, 3. -100 is used to illustrated unused values:

    [1 (head) (tail), -100, -100, -100, -100]
    [1 (head), 2 (tail), -100, -100, -100]
    [1 (head), 2, 3 (tail), -100, -100]

When we read a value, we start with 1:

    [-100, 2 (head), 3 (tail), -100, -100]

We than add 4, 5, 6 and have this:

    [-100, 2 (head), 3, 4 (tail), -100]
    [-100, 2 (head), 3, 4, 5 (tail)]
    [6 (tail), 2 (head), 3, 4, 5]

Note that tail is now behind head, and we're out of room. Our next insert of 7 doubles the array size, and cleans up the ordering:

    [2(head), 3, 4, 5, 6, 7(tail), -100, -100, -100, -100]

Then read a few more times until it's empty:

    [-100, 3(head), 4, 5, 6, 7 (tail), -100, -100, -100, -100] 
    [-100, -100, 4(head), 5, 6, 7 (tail), -100, -100, -100, -100]
    [-100, -100, -100, 5(head), 6, 7 (tail), -100, -100, -100, -100]
    [-100, -100, -100, -100, 6 (head), 7 (tail), -100, -100, -100, -100]
    [-100, -100, -100, -100, -100, 7 (head) (tail), -100, -100, -100, -100]
    [-100, -100, -100, -100, -100, -100 (head) (tail), -100, -100, -100, -100]

Then add 8 to show the queue cleaning itself up:

    [8 (head) (tail), -100, -100, -100, -100, -100, -100, -100, -100, -100]

