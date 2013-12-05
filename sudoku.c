//
//  sudoku.c
//
//  Sudoku Solver
//
//  Uses elimination to solve. This won't work on very difficult puzzles.
//
//  Created by Blake Caldwell on 12/3/13.
//  Copyright (c) 2013 Blake Caldwell. All rights reserved.
//

#include <stdio.h>
#include "sudoku.h"

// given a row or column, find the starting quadrant row or column - either 0, 3, 6
int box_quadrant_start(int row_or_col);

// remove a possibility from a grid cell
int remove_possibility(struct sudoku_grid *grid, unsigned int row, unsigned int col, unsigned int value);

// see if there's only one possibilty for a cell - if so, return it, else 0
unsigned int get_only_possibility(struct sudoku_grid *grid, unsigned int row, unsigned int col);

// set a value on the grid
int set_grid_value(struct sudoku_grid *grid, unsigned int row, unsigned int col, unsigned int val);

// find a cell with the fewest number of possibilities
int cell_with_fewest_possibilities(struct sudoku_grid *grid, unsigned int *row, unsigned int *col);

// create the grid
struct sudoku_grid create_sudoku_grid()
{
    struct sudoku_grid new_grid;
    for(int row=0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
            // all values are possible at the start
            for(int value=0; value<9; value++)
            {
                new_grid.possibilities[row][col][value] = 1;
            }
            new_grid.possibility_count[row][col] = 9;
            new_grid.values[row][col] = 0;
        }
    }
    return new_grid;
}

// Set the starting values on the input sudoku grid.
//
// Template:
//initialize_grid(grid, (int[9][9]){
//    {0, 0, 0,   0, 0, 0,    0, 0, 0},
//    {0, 0, 0,   0, 0, 0,    0, 0, 0},
//    {0, 0, 0,   0, 0, 0,    0, 0, 0},
//    
//    {0, 0, 0,   0, 0, 0,    0, 0, 0},
//    {0, 0, 0,   0, 0, 0,    0, 0, 0},
//    {0, 0, 0,   0, 0, 0,    0, 0, 0},
//    
//    {0, 0, 0,   0, 0, 0,    0, 0, 0},
//    {0, 0, 0,   0, 0, 0,    0, 0, 0},
//    {0, 0, 0,   0, 0, 0,    0, 0, 0}
//});
//
int initialize_grid(struct sudoku_grid *grid, unsigned int starting_values[9][9])
{
    int starting_value;
    
    for(int row=0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
            // see if we have a starting value for this cell
            starting_value = starting_values[row][col];
            
            // ignore 0's
            if(starting_value)
            {
                set_grid_value(grid, row, col, starting_value);
            }
        }
    }
    return 1;
}


// Set a grid value - removes this value from the neighbors' list of possibilities.
// Re-evaluate the neighbors and set their values if they now only have one possibility.
int set_grid_value(struct sudoku_grid *grid, unsigned int row, unsigned int col, unsigned int val)
{
    int possibilities_were_removed = 0;
    
    // set the cell value
    grid->values[row][col] = val;
    
    // no more possibilities for this cell
    grid->possibility_count[row][col] = 0;
    for(int i=0; i<9; i++)
    {
        grid->possibilities[row][col][i] = 0;
    }
    
    // figure out which box this is in
    int box_row_start = box_quadrant_start(row);
    int box_col_start = box_quadrant_start(col);
    
    // remove the value from all in this grid's 3x3 box
    for(int box_row = box_row_start; box_row < box_row_start+3; box_row++)
    {
        for(int box_col = box_col_start; box_col < box_col_start+3; box_col++)
        {
            possibilities_were_removed |= remove_possibility(grid, box_row, box_col, val);
        }
    }
    
    // remove the value from all in the cell's row
    for(int i=0; i<9; i++)
    {
        possibilities_were_removed |= remove_possibility(grid, row, i, val);
    }
    
    // remove the value from all in the cell's column
    for(int i=0; i<9; i++)
    {
        possibilities_were_removed |= remove_possibility(grid, i, col, val);
    }
    
    // if we removed possibilities, recurse
    if(possibilities_were_removed)
    {
        int only_possibility;
        for(int r=0; r<9; r++)
        {
            for(int c=0; c<9; c++)
            {
                only_possibility = get_only_possibility(grid, r, c);
                if(only_possibility)
                {
                    set_grid_value(grid, r, c, only_possibility);
                }
            }
        }
    }
    
    return 1;
}

// given the input row or column index, return the starting index for that axis's quadrant
int box_quadrant_start(int row_or_col)
{
    if(row_or_col < 3)
    {
        return 0;
    }
    if(row_or_col < 6)
    {
        return 3;
    }
    return 6;
}

// remove a value for the input cell
// return 1 if a change was made, 0 if not
int remove_possibility(struct sudoku_grid *grid, unsigned int row, unsigned int col, unsigned int value)
{
    if(grid->possibilities[row][col][value-1])
    {
        // this value already was a possibility
        grid->possibilities[row][col][value-1] = 0;
        grid->possibility_count[row][col]--;
        
        return 1;
    }
    return 0;
}

// given the input grid, row, and column, if there's only one possibility and no current value, return it, else return 0
unsigned int get_only_possibility(struct sudoku_grid *grid, unsigned int row, unsigned int col)
{
    // check if we have a value already
    unsigned int existing_value = grid->values[row][col];
    if(existing_value)
    {
        // this cell is already solved
        return 0;
    }
    
    if(1 == grid->possibility_count[row][col])
    {
        // find which value it is
        for(int i=0; i<9; i++)
        {
            if(grid->possibilities[row][col][i])
            {
                // the only possible value for this cell is i+1
                return i+1;
            }
        }
    }
    
    // more than one possibility
    return 0;
}

// return 1 if the grid is complete, 0 if not
int is_sudoku_grid_complete(struct sudoku_grid *grid)
{
    for(int row=0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
            if(!grid->values[row][col])
            {
                return 0;
            }
        }
    }
    return 1;
}

// solve the input grid by trying combinations of possibilities
// return 1 if we solve the puzzle, 0 if there's nothing more to check
int solve_by_searching(struct sudoku_grid **grid)
{
    unsigned int row;
    unsigned int col;
    
    if(!cell_with_fewest_possibilities(*grid, &row, &col))
    {
        // base case: nothing more to do!
        if(is_sudoku_grid_complete(*grid))
        {
            // woo hoo, we solved it!
            return 1;
        }
        
        // nothing more to do, but we didn't solve it - dead end, bad set of combinations
        return 0;
    }
    
    // we're not solved yet - try each of the possibilities for this cell, with a new copy of the grid
    for(int i=0; i<9; i++)
    {
        if((*grid)->possibilities[row][col][i])
        {
            // i+1 is a possibility - set it, then recurse with it
            struct sudoku_grid new_grid = **grid;
            set_grid_value(&new_grid, row, col, i+1);
            
            // recurse
            struct sudoku_grid *new_grid_ptr = &new_grid;
            if(solve_by_searching(&new_grid_ptr))
            {
                // solved!
                *grid = new_grid_ptr;
                return 1;
            }
        }
    }
    return 0;
}

// find a cell with the fewest number of possibilities
// return 0 if there are no more possibilities
int cell_with_fewest_possibilities(struct sudoku_grid *grid, unsigned int *row, unsigned int *col)
{
    int min = 10;
    for(int r=0; r<9; r++)
    {
        for(int c=0; c<9; c++)
        {
            if(grid->possibility_count[r][c] > 0 && grid->possibility_count[r][c] < min)
            {
                // found our least number of possibilities so far
                min = grid->possibility_count[r][c];
                *row = r;
                *col = c;
            }
        }
    }
    return min != 10;
}

// print the grid
int print_sudoku_grid(struct sudoku_grid *grid)
{
    for(int row=0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
            printf("%i ", grid->values[row][col]);
            if(2 == col || 5 == col)
            {
                printf("| ");
            }
        }
        printf("\n");
        if(2 == row || 5 == row)
        {
            printf("------+-------+------\n");
        }
    }
    printf("\n");
    return 1;
}
