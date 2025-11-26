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
    
    printf("AI's turn (%c): \n", player == 1 ? 'X' : 'O');

    for (int k = 0; k < 2; k++) {
        if (k == 1) playerCheck *= -1;
        
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                // Horizontal XX_
                if (j < boardSize - 2 && board[i][j] == playerCheck && 
                    board[i][j] == board[i][j + 1] && board[i][j + 2] == 0) {
                    row = i; col = j + 2;
                    break;
                }
                // Horizontal X_X
                if (j < boardSize - 2 && board[i][j] == playerCheck && 
                    board[i][j + 2] == playerCheck && board[i][j + 1] == 0) {
                    row = i; col = j + 1;
                    break;
                }
                
                // Vertical XX_
                if (i < boardSize - 2 && board[i][j] == playerCheck && 
                    board[i][j] == board[i + 1][j] && board[i + 2][j] == 0) {
                    row = i + 2; col = j;
                    break;
                }
                // Vertical X_X
                if (i < boardSize - 2 && board[i][j] == playerCheck && 
                    board[i + 2][j] == playerCheck && board[i + 1][j] == 0) {
                    row = i + 1; col = j;
                    break;
                }
                
                // Diagonal Right Down XX_
                if (i < boardSize - 2 && j < boardSize - 2 && board[i][j] == playerCheck && 
                    board[i][j] == board[i + 1][j + 1] && board[i + 2][j + 2] == 0) {
                    row = i + 2; col = j + 2;
                    break;
                }
                // Diagonal Right Down X_X
                if (i < boardSize - 2 && j < boardSize - 2 && board[i][j] == playerCheck && 
                    board[i + 2][j + 2] == playerCheck && board[i + 1][j + 1] == 0) {
                    row = i + 1; col = j + 1;
                    break;
                }
                
                // Diagonal Left Down XX_
                if (i < boardSize - 2 && j >= 2 && board[i][j] == playerCheck && 
                    board[i][j] == board[i + 1][j - 1] && board[i + 2][j - 2] == 0) {
                    row = i + 2; col = j - 2;
                    break;
                }
                // Diagonal Left Down X_X
                if (i < boardSize - 2 && j >= 2 && board[i][j] == playerCheck && 
                    board[i + 2][j - 2] == playerCheck && board[i + 1][j - 1] == 0) {
                    row = i + 1; col = j - 1;
                    break;
                }
            }
            if (row != -1) break;
        }
        if (row != -1) break;
    }

    if (row == -1 || col == -1) {
        // Random move
        do {
            row = rand() % boardSize;
            col = rand() % boardSize;
        } while (board[row][col] != 0);
    }
    
    board[row][col] = player;
}

int checkWin(int boardSize, int board[][MAXSIZE])
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            // Check only if current cell is not empty
            if (board[i][j] == 0) continue;
            
            // Horizontal 
            if (j + 2 < boardSize && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2])
                return board[i][j];
            
            // Vertical 
            if (i + 2 < boardSize && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j])
                return board[i][j];
            
            // Diagonal Right Down
            if (i + 2 < boardSize && j + 2 < boardSize && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2])
                return board[i][j];
            
            // Diagonal Left Down
            if (i + 2 < boardSize && j >= 2 && board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2])
                return board[i][j];
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