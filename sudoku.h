//
//  sudoku.h
//
//  Sudoku Solver
//
//  Uses elimination and possibility searching to solve any Sudoku puzzle.
//
//  Created by Blake Caldwell on 12/3/13.
//  Copyright (c) 2013 Blake Caldwell. All rights reserved.
//

#ifndef Practice_sudoku_h
#define Practice_sudoku_h

struct sudoku_grid
{
    // keep track of all remaining possibilities
    unsigned int possibilities[9][9][9];            // [row][col][is value-1 possible] - 0 if not, 1 if so
    unsigned int possibility_count[9][9];           // number of possibilities per [row][col]
    
    // the known value at any cell
    unsigned int values[9][9];                      // [row][col] - 0 means not set
};

// create the grid
struct sudoku_grid create_sudoku_grid();

// set the starting values on the input sudoku grid
int initialize_grid(struct sudoku_grid *grid, unsigned int starting_values[9][9]);

// return 1 if the grid is complete, 0 if not
int is_sudoku_grid_complete(struct sudoku_grid *grid);

// solve the input grid by trying combinations of possibilities
// return 1 on success
int solve_by_searching(struct sudoku_grid **grid);

// print the grid
int print_sudoku_grid(struct sudoku_grid *grid);

#endif
