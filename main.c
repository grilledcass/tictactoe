#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
#define MAXSIZE 13

int main()
{
    // Initializing variables
    int boardSize = 0;
    int playWithAI = 0;
    int turn = 1;
    int winner = 0;
    int playAgain = 0;
    int firstHandWho = 1; // 1 for player 1, -1 for AI/player 2
    // Score variables
    int scorePlayer1 = 0;
    int scorePlayer2 = 0; //Also for AI
    
    
    while (boardSize < 3 || boardSize > MAXSIZE-3){
        printf("Enter the board size (max %d): ", MAXSIZE-3);
        scanf("%d", &boardSize);
    }
    int board[MAXSIZE][MAXSIZE];

    // Intializing empty board
    initializeBoard(MAXSIZE, board); 

    // Asking if user wants to play with AI
    do
    {
        printf("Do you want to play with AI? (1 for Yes, 0 for No): ");
        scanf("%d", &playWithAI);
    } while (playWithAI != 1 && playWithAI != 0);

    printBoard(boardSize, board);

    // Game loop
    do{
    do{
        if (checkDraw(boardSize, board)) break; //Break if it's a draw
        winner = checkWin(boardSize, board);
        if (isThereWinner(winner, playWithAI)) break; //Break if someone won
        // Decision Logic for who takes the next move
        if (firstHandWho != turn)
            if (playWithAI)
                AIMove(boardSize, turn, board);
            else
                playerMove(boardSize, turn, board);
        else 
            playerMove(boardSize, turn, board);
           
        printBoard(boardSize, board);
        turn *= -1;
    } while (1);
        if (winner == 1)
            scorePlayer1 = updateScore(scorePlayer1);
        else if (winner == -1)
            scorePlayer2 = updateScore(scorePlayer2);
        printf("Do you want to play again? (1 for Yes, 0 for No): ");
        scanf("%d", &playAgain);
    }while (playAgain == 1);
    return 0;
}

