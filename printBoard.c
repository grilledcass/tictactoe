#include <stdio.h> 


int main(void){
    extern char board[];
    printf(" %s | %s | %s \n %s | %s | %s \n %s | %s | %s \n", board[0],board[1],board[2],board[3],board[4],board[5],board[6],board[7],board[8]);
}