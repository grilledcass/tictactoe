#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXSIZE 10 

int main(){
    //Initializing boardsize
    int boardSize = 0;
    int playWithAI = 0;
    while (boardSize < 3 || boardSize > MAXSIZE){
        printf("Enter the board size (max %d): ", MAXSIZE);
        scanf("%d", &boardSize);
    }
    char board[boardSize][boardSize];

    //Asking if user wants to play with AI
    do{
        printf("Do you want to play with AI? (1 for Yes, 0 for No): ");
        scanf("%d", &playWithAI);
    } while (playWithAI != 1 && playWithAI != 0);

    return 0;
}



