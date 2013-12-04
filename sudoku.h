//
//  sudoku.h
//
//  Sudoku Solver
//
//  Uses elimination to solve. This won't work on very difficult puzzles.
//
//  Created by Blake Caldwell on 12/3/13.
//  Copyright (c) 2013 Blake Caldwell. All rights reserved.
//

#ifndef Practice_sudoku_h
#define Practice_sudoku_h

struct sudoku_grid
{
    // keep track of all remaining possibilities
    unsigned int possibilities[9][9];         // [row][col] - bitmask, 0-8 bits are set
    
    // the known value at any cell
    unsigned int *values;                     // [row][col] - 0 means not set
};

// create the grid
int create_sudoku_grid(struct sudoku_grid **grid);

// set the starting values on the input sudoku grid
int initialize_grid(struct sudoku_grid *grid, unsigned int starting_values[9][9]);

// destroy the grid
int destroy_sudoku_grid(struct sudoku_grid **grid);

// set a value on the grid
int set_grid_value(struct sudoku_grid *grid, unsigned int row, unsigned int col, unsigned int val);

// return 1 if the grid is complete, 0 if not
int is_sudoku_grid_complete(struct sudoku_grid *grid);

// print the grid
int print_sudoku_grid(struct sudoku_grid *grid);

#endif
