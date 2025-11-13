#ifndef MATHUTILS_H
#define MATHUTILS_H
#define MAXSIZE 10
// The above ensure no duplication if the header file is defined elsewhere or
// included multiple times within the project

/* Function prototypes */
void printBoard(int boardSize, int board[][MAXSIZE]);
void playerMove(int boardSize, int player, int board[][MAXSIZE]);

#endif