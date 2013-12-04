c-sudoku-solver
===============

Elimination-Based Sudoku Solver

Note: This won't work on very difficult puzzles - only on those that can be solved with elimination alone.


Details
-------

The sudoku grid is represented as a grid of 9x9 cells, each with a bitmask keeping track of all of the remaining possibilities, if any, and the current value, if known.

    struct sudoku_grid
    {
        // All remaining possibilities - a bitmask; each bit position equal to (value - 1).
        // Set to 0 for cells that are already solved, initialized to 511 (0b111111111)
        unsigned int possibilities[9][9];
        
        // The known value at any cell, indexed as [row][col].
        // Set to 0 if still unknown.
        unsigned int *values;
    };

Each cell's possible values bitmask starts out as 511, which is 111111111 in binary, representing that the initial possible values for a cell are [1, 2, 3, 4, 5, 6, 7, 8, 9]. 

As a cell recieves its initial value, we update the neighbors within that quadrant to remove that value as a possibility by turning off the bit at the index of (value-1). We do the same for every cell in the same row and cell as well. As we remove a possibility from a cell, if that cell has no more possibilities, then we recurse, and set the value on *that* cell.


Limitations
-----------

This only works on puzzles that can be solved via elimination. Included in the project is a demo runner that successfully solves the puzzle found on Wikipedia's entry for Sudoku, and a demo runner that can't solve a difficult Sudoku that requires more complicated logic.


Demo
----

Compile and execute the binary to run the demos in main.c:

	gcc *.c
	./a.out
	
You should see:

	Solved by elimination! :)
	5 3 4 | 6 7 8 | 9 1 2 
	6 7 2 | 1 9 5 | 3 4 8 
	1 9 8 | 3 4 2 | 5 6 7 
	------+-------+------
	8 5 9 | 7 6 1 | 4 2 3 
	4 2 6 | 8 5 3 | 7 9 1 
	7 1 3 | 9 2 4 | 8 5 6 
	------+-------+------
	9 6 1 | 5 3 7 | 2 8 4 
	2 8 7 | 4 1 9 | 6 3 5 
	3 4 5 | 2 8 6 | 1 7 9 
	
	Couldn't solve grid by elimination alone :(
	8 0 0 | 0 0 0 | 0 0 0 
	0 0 3 | 6 0 0 | 0 0 0 
	0 7 0 | 0 9 0 | 2 0 0 
	------+-------+------
	0 5 0 | 0 0 7 | 0 0 0 
	0 0 0 | 0 4 5 | 7 0 0 
	0 0 0 | 1 0 0 | 0 3 0 
	------+-------+------
	0 0 1 | 0 0 0 | 0 6 8 
	0 0 8 | 5 0 0 | 0 1 0 
	0 9 0 | 0 0 0 | 4 0 0 

The first grid is the puzzle found [on Wikipedia](http://en.wikipedia.org/wiki/Sudoku), and the second is [here \("World's hardest sudoku: can you crack it?"\)](http://www.telegraph.co.uk/science/science-news/9359579/Worlds-hardest-sudoku-can-you-crack-it.html).

