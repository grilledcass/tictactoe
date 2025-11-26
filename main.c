#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main(){
    srand(time(NULL));

    int boardSize=0, playWithAI=0, turn=1, winner=0, playAgain=0;
    int scorePlayer1=0, scorePlayer2=0;

    while(boardSize<3 || boardSize>15){
        printf("Enter board size (3-15): ");
        scanf("%d",&boardSize);
    }

    do{
        printf("Play with AI? 1=Yes 0=No: ");
        scanf("%d",&playWithAI);
    } while(playWithAI!=0 && playWithAI!=1);

    GameStats* stats = createGameStats();

    do{
        int** board = createBoard(boardSize);
        initializeBoard(boardSize, board);
        printBoard(boardSize, board);

        GameHistory* history = createGameHistory(boardSize);

        turn = 1;
        do{
            if(checkDraw(boardSize, board)) break;
            winner = checkWin(boardSize, board);
            if(isThereWinner(winner, playWithAI)) break;

            int row, col;
            if((turn==1) || (!playWithAI)){
                playerMove(boardSize, turn, board, &row, &col);
            } else {
                AIMove(boardSize, turn, board, &row, &col);
            }

            addMove(history, row, col, (turn==1)?'X':'O');
            printBoard(boardSize, board);
            turn*=-1;
        } while(1);

        if(winner==1) scorePlayer1 = updateScore(scorePlayer1);
        else if(winner==-1) scorePlayer2 = updateScore(scorePlayer2);

        printf("Score - Player1 (X): %d | Player2/O (O): %d\n", scorePlayer1, scorePlayer2);
        
        updateStats(stats, winner==1?'X':winner==-1?'O':'D', winner);
        saveReplay(history, "last_game.replay");

        freeGameHistory(history);
        freeBoard(board, boardSize);

        printStatistics(stats);

        char replayChoice;
        printf("Do you want to replay the last game? (y/n): ");
        scanf(" %c", &replayChoice);
        if(replayChoice=='y' || replayChoice=='Y'){
            playReplay("last_game.replay");
        }

        printf("Play again? 1=Yes, other=No: ");
        scanf("%d",&playAgain);

    } while(playAgain==1);

    freeGameStats(stats);
    return 0;
}