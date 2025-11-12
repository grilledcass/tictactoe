#include <stdio.h>
#include "functions.h"

void printboard(int boardSize, int board[][MAXSIZE]) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j]){
                if (board[i][j] == 1)
                    printf("X ");
                else if (board[i][j] == 2)
                    printf("O ");
            }else
                printf("  ");
        }
        printf("\n");
    }
}
