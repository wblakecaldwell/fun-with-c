//
//  main.c
//
//  Sudoku Solver - demo runner
//
//  Created by Blake Caldwell on 11/18/13.
//  Copyright (c) 2013 Blake Caldwell. All rights reserved.
//

#include <stdio.h>
#import "sudoku.h"

void successful_attempt();
void unsuccessful_attempt();
void solve_and_destroy(struct sudoku_grid **grid);

int main(int argc, const char * argv[])
{
    successful_attempt();
    
    unsuccessful_attempt();
}

//
// Example of a successfully-solved Sudoku puzzle.
// Puzzle is able to be solved by elimination alone.
//
// Wikipedia's Sudoku example: http://en.wikipedia.org/wiki/Sudoku
//
void successful_attempt()
{
    struct sudoku_grid *grid;
    
    create_sudoku_grid(&grid);
    initialize_grid(grid, (unsigned int[9][9]){
        {5, 3, 0,   0, 7, 0,    0, 0, 0},
        {6, 0, 0,   1, 9, 5,    0, 0, 0},
        {0, 9, 8,   0, 0, 0,    0, 6, 0},
        
        {8, 0, 0,   0, 6, 0,    0, 0, 3},
        {4, 0, 0,   8, 0, 3,    0, 0, 1},
        {7, 0, 0,   0, 2, 0,    0, 0, 6},
        
        {0, 6, 0,   0, 0, 0,    2, 8, 0},
        {0, 0, 0,   4, 1, 9,    0, 0, 5},
        {0, 0, 0,   0, 8, 0,    0, 7, 9}
    });
    solve_and_destroy(&grid);
}


//
// Example of an unsuccessfully-solved Sudoku puzzle.
// Puzzle is unable to be solved by elimination alone.
//
// "World's hardest sudoku: can you crack it?"
// http://www.telegraph.co.uk/science/science-news/9359579/Worlds-hardest-sudoku-can-you-crack-it.html
//
void unsuccessful_attempt()
{
    struct sudoku_grid *grid;
    
    create_sudoku_grid(&grid);
    initialize_grid(grid, (unsigned int[9][9]){
        {8, 0, 0,   0, 0, 0,    0, 0, 0},
        {0, 0, 3,   6, 0, 0,    0, 0, 0},
        {0, 7, 0,   0, 9, 0,    2, 0, 0},
        
        {0, 5, 0,   0, 0, 7,    0, 0, 0},
        {0, 0, 0,   0, 4, 5,    7, 0, 0},
        {0, 0, 0,   1, 0, 0,    0, 3, 0},
        
        {0, 0, 1,   0, 0, 0,    0, 6, 8},
        {0, 0, 8,   5, 0, 0,    0, 1, 0},
        {0, 9, 0,   0, 0, 0,    4, 0, 0}
    });
    solve_and_destroy(&grid);
}

// solve the puzzle, print it, and then clean up
void solve_and_destroy(struct sudoku_grid **grid)
{
    if(!is_sudoku_grid_complete(*grid))
    {
        printf("Couldn't solve grid by elimination alone :(\n");
    }
    else
    {
        printf("Solved by elimination! :)\n");
    }
    print_sudoku_grid(*grid);
    destroy_sudoku_grid(grid);
}
