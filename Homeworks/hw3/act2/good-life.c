// 
// File: good-life.c   
// Description: Play a game of Conway's Game of Life using a randomly placed,
// but user defined quiantity, set of living cells that move through 100
// generations
// 
// @author Clinten Hopkins (cmh3586)
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>

/// Output the header to the stdout
void header(void)
{
      printf("\n\t..Welcome to the Game of life..\n");
}

/// Calculate the number of "neighbors" (living cells) for a given cell
///
/// @param size integer number of rows and columns of the 2D array
/// @param life 2D char array that represents the game board we want to look
///         through to find the neighbors
/// @param row integer value represent the row of the cell we want to find the
///         neighbors of
/// @param col integer value represent the col of the cell we want to find the
///         neighbors of
/// @returns integer number of living cells surrounding the defined cell
int calculateNeighbors(int size, char life[size][size], int row, int col) 
{

    int neighbors = 0;

    int lowRow = ((row - 1) % size + size) % size;
    int highRow = ((row + 1) % size + size) % size;
    int lowCol = ((col - 1) % size + size) % size;
    int highCol = ((col + 1) % size + size) % size;

    if(life[lowRow][lowCol] == '*')
        neighbors++;
    if(life[lowRow][col] == '*')
        neighbors++;
    if(life[lowRow][highCol] == '*')
        neighbors++;
    if(life[row][lowCol] == '*')
        neighbors++;
    if(life[row][highCol] == '*')
        neighbors++;
    if(life[highRow][lowCol] == '*')
        neighbors++;
    if(life[highRow][col] == '*')
        neighbors++;
    if(life[highRow][highCol] == '*')
        neighbors++;

    return neighbors;
}

/// Apply Conway's rules to every cell in the old game board and output the
/// new living cells to a new game board.
/// The rules are as follows:
///     1) Any live cell with two or three live neighbours survives.
///     2) Any dead cell with three live neighbours becomes a live cell.
///     3) All other live cells die in the next generation. Similarly, all other dead cells stay dead.
///
/// @param size integer number of rows and columns of the 2D array
/// @param life 2D char array that represents the game board we want to look
///         through to calculate the new living cells
/// @param newLife 2D char array that represents the game board we want to output
///         our new living cells to
void applyRules(int size, char life[size][size], char newLife[size][size])
{

    for(int row = 0; row<size; row++)
    {
        for(int col = 0; col<size; col++)
        {
            int neighbors = calculateNeighbors(size, life, row, col);
            if(life[row][col] == ' ') //fix 7: changed the string literal " " to a char ' ' fix 12: removed the integer casting from life[row][col
            {
                if(neighbors == 3) 
                {
                    //Rule 1
                    newLife[row][col] = '*'; //fix 6: replace == with =, assign the value rather than compare to it
                }
            } else {
                if(neighbors == 2 || neighbors == 3)
                {
                    //Rule 2
                    newLife[row][col] = '*'; //fix 9: replace == with =, assign the value rather than compare to it
                } else {
                    //Rule 3
                    newLife[row][col] = ' '; //added ability to die
                }
            }
        }
    } 
}
/// Main function for Conway's Game of Life
///
/// @returns EXIT_SUCCESS
int main(void)
{
    int size = 20;
    char newLife[size][size], life[size][size];
    int orgs; //fix 3: removed the unused var int gens
    int i, row, col; //fix 4: removed the unused vars int a & b
    int count = 0;
    //fix 14: removed unused var int x = 19 and unused var int y = 19
    //fix 5: removed the unused var char ans

    header();

    printf("\nPlease enter the initial number of organisms: ");
    scanf("%i", &orgs);

    srand( 31 );

    for(i = 0; i < orgs; i++)
    {
        do {
            row = rand();
            row %= size;
            col = rand();
            col %= size;
        } while (newLife[row][col] == '*'); //Added a do while to allow the method to continue to generate a
                                         //random position until it finds one that isnt already a '*'
        newLife[row][col] = '*'; //fix 2: replace == with =, assign the value rather than compare to it
    }

//  newLife[1][0] = '*';
//  newLife[2][1] = '*';
//  newLife[2][2] = '*';
//  newLife[1][2] = '*';
//  newLife[3][1] = '*';

    for(row = 0; row < size; row++)
    {
        for(col = 0; col < size; col++)
        {
            if(newLife[row][col] != '*')
                newLife[row][col] = ' '; //fix 2: replace == with =, assign the value rather than compare to it
        }
    }

//  for(row = 0; row<20; row++)
//  {
//      for(col = 0; col<20; col++)
//      {
//          printf("%c", life[row][col]); //fix 1: change %s to %c to stop seg fault
//      }
//      puts(" ");
//  }

    while (count < 100) 
    {
        printf("\n");
        for(row = 0; row<size; row++)
        {
            for(col = 0; col<size; col++)
            {
                printf("%c", newLife[row][col]); //fix 1: change %s to %c to stop seg fault
                life[row][col] = newLife[row][col];
            }
            puts(" ");
        }
        printf("\ngeneration: %d\n", count); //fix 15: moved the printf(gen) to above the generation being printed
        applyRules(size, life, newLife); 
        count++;
    }
    return EXIT_SUCCESS;
}
