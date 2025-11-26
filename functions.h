#ifndef MATHUTILS_H
#define MATHUTILS_H
#define MAXSIZE 13
// The above ensure no duplication if the header file is defined elsewhere or
// included multiple times within the project

/* Function prototypes */
void initializeBoard(int boardSize, int board[][MAXSIZE]);
void printBoard(int boardSize, int board[][MAXSIZE]);
void playerMove(int boardSize, int player, int board[][MAXSIZE]);
void AIMove(int boardSize, int player, int board[][MAXSIZE]);
int checkWin(int boardSize, int board[][MAXSIZE]);
int checkDraw(int boardSize, int board[][MAXSIZE]);
int updateScore(int winner);


/*  Ultility functions */
int isThereWinner(int winner, int playWithAI);

#endif