c-array-based-queue
===================

Simple (non-optimal) Array-backed integer FIFO queue in C. 

Note: The underlying array size must be a power of 2. Internally, head and tail roll-over is handled by bitmasking against (array_size - 1).

Details
-------

Rather than use a linked list, this queue uses a fixed-size array for its storage. Initially, new values are written to the end of the array, values are read from the beginning. The array's head and tail indices are tracked to handle when the tail of the queue wraps around to the beginning of the array, or if we run out of room and need to double the array. 

Demo
----

Compile and execute the binary to run the unit tests in array_queue_test.c:

    gcc *.c -D SHOW_DEBUG
    ./a.out
    
You should see:

    -----------------------
    Array Queue Tests Pass!
    -----------------------
    
The demo performs the following:

Initialize a queue with size 4, then insert 1, 2, 3. -100 is used to illustrated unused values:

    [1 (head) (tail), -100, -100, -100]
    [1 (head), 2 (tail), -100, -100]
    [1 (head), 2, 3 (tail), -100]

When we read a value, we start with 1:

    [-100, 2 (head), 3 (tail), -100]

We than add 4, 5, 6 and have this:

    [-100, 2 (head), 3, 4 (tail)]
    [5 (tail), 2 (head), 3, 4]
    
Note that tail is now behind head, and we're out of room. Our next insert of 6 doubles the array size, and cleans up the ordering:

    [2 (head), 3, 4, 5, 6 (tail), -100, -100, -100]
    
Add 7:
    [2 (head), 3, 4, 5, 6, 7 (tail), -100, -100]

Then read a few more times until it's empty:

    [-100, 3(head), 4, 5, 6, 7 (tail), -100, -100] 
    [-100, -100, 4(head), 5, 6, 7 (tail), -100, -100]
    [-100, -100, -100, 5(head), 6, 7 (tail), -100, -100]
    [-100, -100, -100, -100, 6 (head), 7 (tail), -100, -100]
    [-100, -100, -100, -100, -100, 7 (head) (tail), -100, -100]
    [-100, -100, -100, -100, -100, -100 (head) (tail), -100, -100]

Then add 8 - rather than clean up the ordering (unnecessary), it starst where it left off:

    [-100, -100, -100, -100, -100, -100, 8 (head) (tail), -100]

