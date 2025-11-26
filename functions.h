#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

int** createBoard(int size);
void freeBoard(int** board, int size);
void initializeBoard(int size, int** board);
void printBoard(int size, int** board);
void playerMove(int size, int player, int** board, int* row, int* col);
void AIMove(int size, int player, int** board, int* row, int* col);
int checkWin(int size, int** board);
int checkDraw(int size, int** board);
int isThereWinner(int winner, int playWithAI);
int updateScore(int score);

typedef struct {
    int games_played;
    int wins_player1;
    int wins_player2;
    int draws;
    int* win_patterns;
    int pattern_count;
    int pattern_capacity;
} GameStats;

GameStats* createGameStats();
void updateStats(GameStats* stats, char winner, int win_type);
void freeGameStats(GameStats* stats);
void printStatistics(const GameStats* stats);

typedef struct {
    int move_number;
    int row;
    int col;
    char player;
} GameMove;

typedef struct {
    GameMove* moves;
    int move_count;
    int move_capacity;
    int board_size;
} GameHistory;

GameHistory* createGameHistory(int board_size);
void addMove(GameHistory* history, int row, int col, char player);
void freeGameHistory(GameHistory* history);
void saveReplay(const GameHistory* history, const char* filename);
void playReplay(const char* filename);

#endif