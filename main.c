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

void solve_easy_puzzle();
void solve_hard_puzzle();
void solve(char *name, struct sudoku_grid *grid);

int main(int argc, const char * argv[])
{
    solve_easy_puzzle();
    solve_hard_puzzle();
}

//
// Example of a successfully-solved Sudoku puzzle.
// Puzzle is able to be solved by elimination alone.
//
// Wikipedia's Sudoku example: http://en.wikipedia.org/wiki/Sudoku
//
void solve_easy_puzzle()
{
    struct sudoku_grid grid = create_sudoku_grid();
    initialize_grid(&grid, (unsigned int[9][9]){
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
    solve("Wikipedia's Sudoku", &grid);
}


//
// Example of an unsuccessfully-solved Sudoku puzzle.
// Puzzle is unable to be solved by elimination alone.
//
// "World's hardest sudoku: can you crack it?" (YES!)
// http://www.telegraph.co.uk/science/science-news/9359579/Worlds-hardest-sudoku-can-you-crack-it.html
//
void solve_hard_puzzle()
{
    struct sudoku_grid grid = create_sudoku_grid();
    initialize_grid(&grid, (unsigned int[9][9]){
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
    solve("World's Hardest Sudoku", &grid);
}

// solve the puzzle, print it, and then clean up
void solve(char *name, struct sudoku_grid *grid)
{
    if(!is_sudoku_grid_complete(grid))
    {
        printf("Couldn't solve %s by elimination alone\n", name);
        print_sudoku_grid(grid);
        if(solve_by_searching(&grid))
        {
            printf("Solved %s by searching\n", name);
            print_sudoku_grid(grid);
        }
        else
        {
            printf("Couldn't solve %s by searching\n", name);
        }
    }
    else
    {
        printf("Solved %s by elimination\n", name);
        print_sudoku_grid(grid);
    }
}
