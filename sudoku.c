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
#include <stdlib.h>
#include "sudoku.h"

int box_quadrant_start(int row_or_col);
unsigned int turn_on_bit(unsigned int *value, unsigned int bit_index);
unsigned int turn_off_bit(unsigned int *value, unsigned int bit_index);
int get_only_possibility(int possibilities);

// create the grid
int create_sudoku_grid(struct sudoku_grid **grid)
{
    struct sudoku_grid *new_grid = malloc(sizeof(struct sudoku_grid));
    unsigned int *values = calloc(9*9, sizeof(int));
    for(int row=0; row<9; row++)
    {
        for(int col=0; col<9; col++)
        {
            // 511 == bits 0-8 on, which means values 1-9 is possible
            new_grid->possibilities[row][col] = 511;
        }
    }
    new_grid->values = values;
    
    *grid = new_grid;
    return 1;
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

// free all memory in a sudoku grid
int destroy_sudoku_grid(struct sudoku_grid **grid)
{
    if(NULL != *grid)
    {
        free((*grid)->values);
        free(*grid);
        *grid = NULL;
    }
    return 1;
}

// Set a grid value - removes this value from the neighbors' list of possibilities.
// Re-evaluate the neighbors and set their values if they now only have one possibility.
int set_grid_value(struct sudoku_grid *grid, unsigned int row, unsigned int col, unsigned int val)
{
    // set the cell value
    grid->values[9 * row + col] = val;
    grid->possibilities[row][col] = 0;
    
    // figure out which box this is in
    int box_row_start = box_quadrant_start(row);
    int box_col_start = box_quadrant_start(col);
    
    // after removing a remaining option, we check if there's only one possibilty left
    int only_possibility;
    
    // remove the value from all in this grid's 3x3 box
    for(int box_row = box_row_start; box_row < box_row_start+3; box_row++)
    {
        for(int box_col = box_col_start; box_col < box_col_start+3; box_col++)
        {
            if(!grid->values[box_row * 3 + box_col])
            {
                // remove the possibility from its neighbors
                turn_off_bit(&(grid->possibilities[box_row][box_col]), val - 1);
                
                // see if the neighbor only has one possibility now
                only_possibility = get_only_possibility(grid->possibilities[row][col]);
                if(only_possibility)
                {
                    set_grid_value(grid, row, col, only_possibility);
                }
            }
        }
    }
    
    // remove the value from all in the cell's row
    for(int i=0; i<9; i++)
    {
        turn_off_bit(&(grid->possibilities[row][i]), val - 1);
        
        // see if the neighbor only has one possibility now
        only_possibility = get_only_possibility(grid->possibilities[row][i]);
        if(only_possibility)
        {
            set_grid_value(grid, row, i, only_possibility);
        }
    }
    
    // remove the value from all in the cell's column
    for(int i=0; i<9; i++)
    {
        turn_off_bit(&(grid->possibilities[i][col]), val - 1);
        
        // see if the neighbor only has one possibility now
        only_possibility = get_only_possibility(grid->possibilities[i][col]);
        if(only_possibility)
        {
            set_grid_value(grid, i, col, only_possibility);
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

// given the input remaining possibilty mask, if there's only one possibility, return it, else return 0
int get_only_possibility(int possibilities)
{
    static int single_bit[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    for(int i=0; i<9; i++)
    {
        if(possibilities == single_bit[i])
        {
            // input remaining possibilities was a single on bit - return the value that it represents
            return i + 1;
        }
    }
    
    // input remaining possibilities had more than one bit set
    return 0;
}

// turn a specific bit index on in value
unsigned int turn_on_bit(unsigned int *value, unsigned int bit_index)
{
    static int bitmask[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    *value |= bitmask[bit_index];
    return *value;
}

// turn a specific bit index off in value
unsigned int turn_off_bit(unsigned int *value, unsigned int bit_index)
{
    static unsigned int bitmask[9] = {510, 509, 507, 503, 495, 479, 447, 383, 255};
    *value &= bitmask[bit_index];
    return *value;
}

// return 1 if the grid is complete, 0 if not
int is_sudoku_grid_complete(struct sudoku_grid *grid)
{
    for(int i=0; i<81; i++)
    {
        if(grid->values[i] == 0)
        {
            // missing value
            return 0;
        }
    }
    return 1;
}

// print the grid
int print_sudoku_grid(struct sudoku_grid *grid)
{
    for(int i=0; i<81; i++)
    {
        printf("%i ", grid->values[i]);
        if((i+1) % 9 == 3 || (i+1) % 9 == 6)
        {
            printf("| ");
        }
        if((i+1) % 9 == 0)
        {
            printf("\n");
        }
        if(i == 26 || i == 53)
        {
            printf("------+-------+------\n");
        }
    }
    printf("\n\n");
    return 1;
}
