#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "functions.h"

void initializeBoard(int boardSize, int board[][MAXSIZE])
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j] = 0;
        }
    }
}
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
    if (player == 1)
        printf("Player 1's turn (X): \n");
    else
        printf("Player 2's turn (O): \n");

    do
    {
        printf("Enter your move (row and column): ");
        scanf("%d %d", &row, &col);
    } while (row <= 0 || row > boardSize || col <= 0 || col > boardSize || !(board[row - 1][col - 1] == 0));

    board[row - 1][col - 1] = player;
}

void AIMove(int boardSize, int player, int board[][MAXSIZE])
{
    int row = -1, col = -1;
    int playerCheck = player;
    if (player == 1)
        printf("AI's turn (X): \n");
    else
        printf("AI's turn (O): \n");

    for (int k = 0; k < 2; k++){ //First check, check if they are winning (k==0)
        if (k == 1)
            playerCheck *= -1;   //Second check, block opponent's winning move
        for (int i = 0; i < boardSize; i++){
            for (int j = 0; j < boardSize; j++){
                // Horizontal
                if (j < (boardSize - 2))
                    if (board[i][j] == board[i][j + 1] && board[i][j] == playerCheck && board[i][j + 2] == 0)
                    {
                        row = i;
                        col = j + 2;
                    }
                // Vertical
                if (i < (boardSize - 2))
                    if (board[i][j] == board[i + 1][j] && board[i][j] == playerCheck && board[i + 2][j] == 0)
                    {
                        row = i + 2;
                        col = j;
                    }
                // Diagonal Right Down
                if (j < (boardSize - 2) && i < (boardSize - 2))
                    if (board[i][j] == board[i + 1][j + 1] && board[i][j] == playerCheck && board[i + 2][j + 2] == 0)
                    {
                        row = i + 2;
                        col = j + 2;
                    }
                // Diagonal Left Down
                if (j >= 2 && i < (boardSize - 2))
                {
                    if (board[i][j] == board[i + 1][j - 1] && board[i][j] == playerCheck && board[i + 2][j - 2] == 0)
                    {
                        row = i + 2;
                        col = j - 2;
                    }
                }
            }
        }
        
    }
    if (row == -1 || col == -1 || row >= boardSize || col >= boardSize){
            // Random move if no strategic move found
            do{
                srand(time(NULL));
                row = rand() % boardSize;
                col = rand() % boardSize;
            } while (board[row][col] != 0);
        }
    board[row][col] = player;
}

int checkWin(int boardSize, int board[][MAXSIZE])
{ // Check rows and columns
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            // Horizontal
            if (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2])
            {
                return board[i][j];
            }
            // Vertical
            if (board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j])
            {
                return board[i][j];
            }
            // Diagonal Right Down
            if (board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2])
            {
                return board[i][j];
            }
            // Diagonal Left Down
            if (j >= 2)
                if (board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2])
                {
                    return board[i][j];
                }
        }
    }
    return 0;
}

int checkDraw(int boardSize, int board[][MAXSIZE])
{
    for (int i = 0; i < boardSize; i++)
        for (int j = 0; j < boardSize; j++)
            if (board[i][j] == 0)
                return 0;
    printf("It's a draw!\n");
    return 1;
}

int isThereWinner(int winner, int playWithAI)
{
    if (winner == 1)
        printf("Player 1 (X) wins!\n");
    else if (winner == -1)
        if (playWithAI)
            printf("AI (O) wins!\n");
        else
            printf("Player 2 (O) wins!\n");
    else
        return 0;
    return 1;
}

int updateScore(int winner){
    return winner++;
}