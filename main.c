#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

int main(){
    srand(time(NULL));

    int boardSize, playWithAI, turn, winner;
    int score1 = 0, score2 = 0;
    int playAgain;

    GameStats* stats = createGameStats();

    printf("1 = New Game\n2 = Load Saved Game\nChoice: ");
    int mode;
    scanf("%d", &mode);

    int** board;
    GameHistory* history;

    if (mode == 2){
        if (!loadGame("saved_game.dat", &boardSize, &board, &turn, &playWithAI, &score1, &score2, &history)){
            printf("No saved game found.\nStarting new game.\n");
            mode = 1;
        }
    }

    if (mode == 1){
        do {
            printf("Enter board size (3-15): ");
            scanf("%d", &boardSize);
        } while(boardSize < 3 || boardSize > 15);

        do {
            printf("Play with AI? (1=yes 0=no): ");
            scanf("%d", &playWithAI);
        } while(playWithAI!=0 && playWithAI!=1);

        board = createBoard(boardSize);
        initializeBoard(boardSize,board);
        turn = 1;

        history = createGameHistory(boardSize);
    }

    do {
        printBoard(boardSize,board);

        if (checkDraw(boardSize,board)) break;
        winner = checkWin(boardSize,board);
        if (isThereWinner(winner,playWithAI)) break;

        int r,c;

        if (turn==1 || !playWithAI){
            playerMove(boardSize, turn, board, &r, &c);

            if (r == -999){
                saveGame("saved_game.dat", boardSize, board, turn, playWithAI, score1, score2, history);
                printf("Press ENTER to continue.\n");
                getchar(); getchar();
                continue;
            }
        } else {
            AIMove(boardSize, turn, board, &r, &c);
        }

        addMove(history, r, c, (turn==1?'X':'O'));
        turn *= -1;

    } while(1);


    if (winner == 1) score1++;
    else if (winner == -1) score2++;

    printf("Score: P1=%d  P2/AI=%d\n", score1,score2);

    updateStats(stats, winner==1?'X':winner==-1?'O':'D', winner);
    printStatistics(stats);

    printf("Play again? (1=yes): ");
    scanf("%d",&playAgain);

    if (playAgain==1){
        freeBoard(board,boardSize);
        freeGameHistory(history);
        main();  // restart completely safe here
        return 0;
    }

    freeBoard(board,boardSize);
    freeGameHistory(history);
    freeGameStats(stats);

    return 0;
}
