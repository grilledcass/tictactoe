#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
#define MAXSIZE 10

int main()
{
    // Initializing boardsize
    int boardSize = 0;
    int playWithAI = 0;
    while (boardSize <= 3 || boardSize > MAXSIZE)
    {
        printf("Enter the board size (max %d): ", MAXSIZE);
        scanf("%d", &boardSize);
    }
    int board[boardSize][boardSize];

    // Intializing empty board
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j] = 0;
        }
    }

    // Asking if user wants to play with AI
    do
    {
        printf("Do you want to play with AI? (1 for Yes, 0 for No): ");
        scanf("%d", &playWithAI);
    } while (playWithAI != 1 && playWithAI != 0);

    printBoard(boardSize, board);

    do{
        playerMove(boardSize, 1, board);
        printBoard(boardSize, board);
    } while (0);

    return 0;
}
