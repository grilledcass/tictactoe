#include <stdio.h>
#include "functions.h"

void printBoard(int boardSize, int board[][MAXSIZE])
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (board[i][j])
            {
                if (board[i][j] == 1)
                    printf("X ");
                else if (board[i][j] == -1)
                    printf("O ");
            }
            else
                printf(". ");
        }
        printf("\n");
    }
}

void playerMove(int boardSize, int player, int board[][MAXSIZE])
{
    int row, col;
    do
    {
        printf("Enter your move (row and column): ");
        scanf("%d %d", &row, &col);
    } while (row < 0 || row >= boardSize || col < 0 || col >= boardSize || board[row][col] == player*-1);

    board[row-1][col-1] = player; 
}
