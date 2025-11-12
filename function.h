#ifndef FUNCTION_H
#define FUNCTION_H
#define MAXSIZE 10

int playerMove(char board[MAXSIZE][MAXSIZE], int size, char player);
int aiMove(char board[MAXSIZE][MAXSIZE], int size);
int checkWin(char board[MAXSIZE][MAXSIZE], int size);
int checkDraw(char board[MAXSIZE][MAXSIZE], int size);
int updateScore(char winner);

#endif
