#include "functions.h"
#include <time.h>
#include <string.h>

int** createBoard(int size) {
    int** board = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
        board[i] = malloc(size * sizeof(int));
    return board;
}

void freeBoard(int** board, int size) {
    for (int i = 0; i < size; i++)
        free(board[i]);
    free(board);
}

void initializeBoard(int size, int** board) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = 0;
}

void printBoard(int size, int** board) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 1) printf("X ");
            else if (board[i][j] == -1) printf("O ");
            else printf(". ");
        }
        printf("\n");
    }
}

void playerMove(int size, int player, int** board, int* row_out, int* col_out) {
    int row, col;
    if (player == 1) printf("Player 1's turn (X):\n");
    else printf("Player 2's turn (O):\n");

    do {
        printf("Enter move (row col) or S to save: ");

        char buffer[20];
        scanf("%s", buffer);

        if (buffer[0]=='S' || buffer[0]=='s') {
            *row_out = -999;
            return;
        }

        row = atoi(buffer);
        scanf("%d", &col);

    } while (row <= 0 || row > size || col <= 0 || col > size || board[row-1][col-1] != 0);

    board[row-1][col-1] = player;
    *row_out = row-1;
    *col_out = col-1;
}

void AIMove(int size, int player, int** board, int* row_out, int* col_out) {
    int row=-1, col=-1;
    int check = player;
    printf("AI's turn (%c):\n", (player==1?'X':'O'));

    for (int k=0; k<2; k++) {
        if (k==1) check *= -1;

        for (int i=0;i<size;i++){
            for (int j=0;j<size;j++){
                if (j<size-2 && board[i][j]==check && board[i][j+1]==check && board[i][j+2]==0){
                    row=i; col=j+2; goto place;
                }
                if (i<size-2 && board[i][j]==check && board[i+1][j]==check && board[i+2][j]==0){
                    row=i+2; col=j; goto place;
                }
            }
        }
    }

    do {
        row = rand()%size;
        col = rand()%size;
    } while(board[row][col]!=0);

place:
    board[row][col] = player;
    *row_out=row;
    *col_out=col;
}

int checkWin(int size, int** board){
    for (int i=0;i<size;i++){
        for (int j=0;j<size;j++){
            int v = board[i][j];
            if (v==0) continue;

            if (j+2<size && v==board[i][j+1] && v==board[i][j+2]) return v;
            if (i+2<size && v==board[i+1][j] && v==board[i+2][j]) return v;
            if (i+2<size && j+2<size && v==board[i+1][j+1] && v==board[i+2][j+2]) return v;
            if (i+2<size && j>=2 && v==board[i+1][j-1] && v==board[i+2][j-2]) return v;
        }
    }
    return 0;
}

int checkDraw(int size, int** board){
    for (int i=0;i<size;i++)
        for (int j=0;j<size;j++)
            if (board[i][j]==0) return 0;
    printf("It's a draw!\n");
    return 1;
}

int isThereWinner(int winner, int playWithAI){
    if (winner==1) printf("Player 1 (X) wins!\n");
    else if (winner==-1) {
        if (playWithAI) printf("AI (O) wins!\n");
        else printf("Player 2 (O) wins!\n");
    } else return 0;
    return 1;
}

int updateScore(int s){
    return s+1;
}

GameStats* createGameStats(){
    GameStats* s = malloc(sizeof(GameStats));
    s->games_played = s->wins_player1 = s->wins_player2 = s->draws = 0;
    s->pattern_capacity = 10;
    s->pattern_count = 0;
    s->win_patterns = malloc(10 * sizeof(int));
    return s;
}

void updateStats(GameStats* s, char winner, int type){
    s->games_played++;
    if (winner=='X') s->wins_player1++;
    else if (winner=='O') s->wins_player2++;
    else s->draws++;

    if (s->pattern_count == s->pattern_capacity){
        s->pattern_capacity *= 2;
        s->win_patterns = realloc(s->win_patterns, s->pattern_capacity*sizeof(int));
    }
    s->win_patterns[s->pattern_count++] = type;
}

void freeGameStats(GameStats* s){
    free(s->win_patterns);
    free(s);
}

void printStatistics(const GameStats* s){
    printf("\n--- Game Statistics ---\n");
    printf("Games Played: %d\n", s->games_played);
    printf("Player 1 Wins: %d\n", s->wins_player1);
    printf("Player 2 Wins: %d\n", s->wins_player2);
    printf("Draws: %d\n", s->draws);
}

GameHistory* createGameHistory(int board_size){
    GameHistory* h = malloc(sizeof(GameHistory));
    h->board_size = board_size;
    h->move_capacity = 50;
    h->move_count = 0;
    h->moves = malloc(h->move_capacity*sizeof(GameMove));
    return h;
}

void addMove(GameHistory* h, int r, int c, char p){
    if (h->move_count == h->move_capacity){
        h->move_capacity *= 2;
        h->moves = realloc(h->moves, h->move_capacity*sizeof(GameMove));
    }
    GameMove* m = &h->moves[h->move_count++];
    m->move_number = h->move_count;
    m->row=r; m->col=c; m->player=p;
}

void freeGameHistory(GameHistory* h){
    free(h->moves);
    free(h);
}

void saveReplay(const GameHistory* h, const char* filename){
    FILE* f = fopen(filename,"w");
    if (!f){ printf("Failed replay save\n"); return; }
    fprintf(f,"%d\n%d\n", h->board_size, h->move_count);
    for (int i=0;i<h->move_count;i++){
        GameMove m = h->moves[i];
        fprintf(f,"%d %d %d %c\n", m.move_number, m.row, m.col, m.player);
    }
    fclose(f);
}

void playReplay(const char* filename){
    FILE* f = fopen(filename,"r");
    if (!f){ printf("Replay not found.\n"); return; }

    int size, count;
    fscanf(f,"%d %d",&size,&count);

    int** board = createBoard(size);
    initializeBoard(size, board);

    printf("\n--- Replay Start ---\n");
    for (int i=0;i<count;i++){
        int n,r,c;
        char p;
        fscanf(f,"%d %d %d %c",&n,&r,&c,&p);
        board[r][c] = (p=='X'?1:-1);
        printf("Move %d: %c -> (%d,%d)\n", n,p,r+1,c+1);
        printBoard(size, board);
    }

    fclose(f);
    freeBoard(board,size);
}

void saveGame(
    const char* filename,
    int boardSize,
    int** board,
    int turn,
    int playWithAI,
    int score1,
    int score2,
    const GameHistory* h
){
    FILE* f = fopen(filename, "w");
    if (!f){
        printf("Failed to save game!\n");
        return;
    }

    fprintf(f,"%d\n", boardSize);
    fprintf(f,"%d\n", turn);
    fprintf(f,"%d\n", playWithAI);
    fprintf(f,"%d %d\n", score1, score2);

    // board
    for (int i=0;i<boardSize;i++){
        for (int j=0;j<boardSize;j++){
            fprintf(f,"%d ", board[i][j]);
        }
        fprintf(f,"\n");
    }

    // history
    fprintf(f,"%d\n", h->move_count);
    for (int i=0;i<h->move_count;i++){
        GameMove m = h->moves[i];
        fprintf(f,"%d %d %d %c\n", m.move_number, m.row, m.col, m.player);
    }

    fclose(f);
    printf("Game saved successfully!\n");
}

int loadGame(
    const char* filename,
    int* boardSize,
    int*** board,
    int* turn,
    int* playWithAI,
    int* score1,
    int* score2,
    GameHistory** history_out
){
    FILE* f = fopen(filename, "r");
    if (!f) return 0;

    fscanf(f,"%d", boardSize);
    fscanf(f,"%d", turn);
    fscanf(f,"%d", playWithAI);
    fscanf(f,"%d %d", score1, score2);

    *board = createBoard(*boardSize);
    for (int i=0;i<*boardSize;i++)
        for (int j=0;j<*boardSize;j++)
            fscanf(f,"%d", &((*board)[i][j]));

    int moves;
    fscanf(f,"%d", &moves);

    GameHistory* h = createGameHistory(*boardSize);
    for (int i=0;i<moves;i++){
        GameMove m;
        fscanf(f,"%d %d %d %c", &m.move_number,&m.row,&m.col,&m.player);
        addMove(h, m.row, m.col, m.player);
    }

    fclose(f);
    *history_out = h;
    return 1;
}
