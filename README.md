c-sudoku-solver
===============

Details
-------

The Sudoku grid is represented by a C structure with a 3-dimentional array keeping track of which values are still available for each cell, a 2-dimensional array keeping track of how many possibilities are still available for each cell (to help reduce loops), and a 2-dimensional array keeping track of values for solved cells.

    struct sudoku_grid
    {
        // keep track of all remaining possibilities
        unsigned int possibilities[9][9][9];            // [row][col][is value-1 possible] - 0 if not, 1 if so
        unsigned int possibility_count[9][9];           // number of possibilities per [row][col]
        
        // the known value at any cell
        unsigned int values[9][9];                      // [row][col] - 0 means not set
    };


Elimination-Based Solving
-------------------------

As each cell recieves its initial value, we update the neighbors within its quadrant to remove that value as a possibility. We do the same for every cell in the same row and column as well. When a cell has just one remaining possibility we set its value, and then repeat the process of elimination for its surrounding cells.


Search-Based Solving
--------------------

If the grid initialization's elimination phase didn't solve the puzzle, then we can solve by searching. The algorithm finds a cell with the fewest amount of remaining possibilities, picks one, and then recurses until all combinations are tried and the puzzle cannot be solved, or until a solution is found.

Demo
----

Compile and execute the binary to run the demos in main.c:

	gcc *.c
	./a.out
	
You should see:

	Solved Wikipedia's Sudoku by elimination
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
	
	Couldn't solve World's Hardest Sudoku by elimination alone
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
	
	Solved World's Hardest Sudoku by searching
	8 1 2 | 7 5 3 | 6 4 9 
	9 4 3 | 6 8 2 | 1 7 5 
	6 7 5 | 4 9 1 | 2 8 3 
	------+-------+------
	1 5 4 | 2 3 7 | 8 9 6 
	3 6 9 | 8 4 5 | 7 2 1 
	2 8 7 | 1 6 9 | 5 3 4 
	------+-------+------
	5 2 1 | 9 7 4 | 3 6 8 
	4 3 8 | 5 2 6 | 9 1 7 
	7 9 6 | 3 1 8 | 4 5 2 

The first grid is the puzzle can be found [on Wikipedia](http://en.wikipedia.org/wiki/Sudoku), and the second is [here \("World's hardest sudoku: can you crack it?"\)](http://www.telegraph.co.uk/science/science-news/9359579/Worlds-hardest-sudoku-can-you-crack-it.html). The second one can't be solved by elimination alone, so we use the searching algorithm, and reach the [correct solution](http://www.telegraph.co.uk/science/science-news/9360022/Worlds-hardest-sudoku-the-answer.html).

