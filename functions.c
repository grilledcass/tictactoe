#include "functions.h"
#include <time.h>

int** createBoard(int size) {
    int** board = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        board[i] = malloc(size * sizeof(int));
    }
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
        printf("Enter your move (row col): ");
        scanf("%d %d", &row, &col);
    } while (row <= 0 || row > size || col <= 0 || col > size || board[row-1][col-1] != 0);

    board[row-1][col-1] = player;
    *row_out = row-1;
    *col_out = col-1;
}

void AIMove(int size, int player, int** board, int* row_out, int* col_out) {
    int row=-1, col=-1;
    int playerCheck = player;
    printf("AI's turn (%c):\n", player==1?'X':'O');

    for (int k=0;k<2;k++){
        if (k==1) playerCheck*=-1;

        for (int i=0;i<size;i++){
            for (int j=0;j<size;j++){
                if (j<size-2 && board[i][j]==playerCheck && board[i][j]==board[i][j+1] && board[i][j+2]==0){
                    row=i; col=j+2; break;
                }
                if (j<size-2 && board[i][j]==playerCheck && board[i][j+2]==playerCheck && board[i][j+1]==0){
                    row=i; col=j+1; break;
                }
                if (i<size-2 && board[i][j]==playerCheck && board[i][j]==board[i+1][j] && board[i+2][j]==0){
                    row=i+2; col=j; break;
                }
                if (i<size-2 && board[i][j]==playerCheck && board[i+2][j]==playerCheck && board[i+1][j]==0){
                    row=i+1; col=j; break;
                }
                if (i<size-2 && j<size-2 && board[i][j]==playerCheck && board[i][j]==board[i+1][j+1] && board[i+2][j+2]==0){
                    row=i+2; col=j+2; break;
                }
                if (i<size-2 && j<size-2 && board[i][j]==playerCheck && board[i+2][j+2]==playerCheck && board[i+1][j+1]==0){
                    row=i+1; col=j+1; break;
                }
                if (i<size-2 && j>=2 && board[i][j]==playerCheck && board[i][j]==board[i+1][j-1] && board[i+2][j-2]==0){
                    row=i+2; col=j-2; break;
                }
                if (i<size-2 && j>=2 && board[i][j]==playerCheck && board[i+2][j-2]==playerCheck && board[i+1][j-1]==0){
                    row=i+1; col=j-1; break;
                }
            }
            if (row!=-1) break;
        }
        if (row!=-1) break;
    }

    if (row==-1 || col==-1){
        do{
            row = rand() % size;
            col = rand() % size;
        }while(board[row][col]!=0);
    }

    board[row][col] = player;
    *row_out = row;
    *col_out = col;
}

int checkWin(int size, int** board){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(board[i][j]==0) continue;
            if(j+2<size && board[i][j]==board[i][j+1] && board[i][j]==board[i][j+2]) return board[i][j];
            if(i+2<size && board[i][j]==board[i+1][j] && board[i][j]==board[i+2][j]) return board[i][j];
            if(i+2<size && j+2<size && board[i][j]==board[i+1][j+1] && board[i][j]==board[i+2][j+2]) return board[i][j];
            if(i+2<size && j>=2 && board[i][j]==board[i+1][j-1] && board[i][j]==board[i+2][j-2]) return board[i][j];
        }
    }
    return 0;
}

int checkDraw(int size, int** board){
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            if(board[i][j]==0) return 0;
    printf("It's a draw!\n");
    return 1;
}

int isThereWinner(int winner, int playWithAI){
    if(winner==1) printf("Player 1 (X) wins!\n");
    else if(winner==-1) 
        if(playWithAI) printf("AI (O) wins!\n");
        else printf("Player 2 (O) wins!\n");
    else return 0;
    return 1;
}

int updateScore(int score){
    return score+1;
}

GameStats* createGameStats(){
    GameStats* s = malloc(sizeof(GameStats));
    s->games_played = s->wins_player1 = s->wins_player2 = s->draws = 0;
    s->pattern_capacity = 10;
    s->pattern_count = 0;
    s->win_patterns = malloc(s->pattern_capacity * sizeof(int));
    return s;
}

void updateStats(GameStats* stats, char winner, int win_type){
    stats->games_played++;
    if(winner=='X') stats->wins_player1++;
    else if(winner=='O') stats->wins_player2++;
    else stats->draws++;

    if(stats->pattern_count==stats->pattern_capacity){
        stats->pattern_capacity*=2;
        stats->win_patterns = realloc(stats->win_patterns, stats->pattern_capacity*sizeof(int));
    }
    stats->win_patterns[stats->pattern_count++] = win_type;
}

void freeGameStats(GameStats* stats){
    free(stats->win_patterns);
    free(stats);
}

void printStatistics(const GameStats* stats){
    printf("\n--- Game Statistics ---\n");
    printf("Games Played: %d\n", stats->games_played);
    printf("Player 1 Wins: %d\n", stats->wins_player1);
    printf("Player 2 Wins: %d\n", stats->wins_player2);
    printf("Draws: %d\n", stats->draws);
}

GameHistory* createGameHistory(int board_size){
    GameHistory* h = malloc(sizeof(GameHistory));
    h->board_size = board_size;
    h->move_capacity = 50;
    h->move_count = 0;
    h->moves = malloc(h->move_capacity * sizeof(GameMove));
    return h;
}

void addMove(GameHistory* h, int row, int col, char player){
    if(h->move_count==h->move_capacity){
        h->move_capacity*=2;
        h->moves = realloc(h->moves, h->move_capacity*sizeof(GameMove));
    }
    GameMove* m = &h->moves[h->move_count++];
    m->move_number = h->move_count;
    m->row = row;
    m->col = col;
    m->player = player;
}

void freeGameHistory(GameHistory* h){
    free(h->moves);
    free(h);
}

void saveReplay(const GameHistory* h, const char* filename){
    FILE* f = fopen(filename,"w");
    if(!f){ printf("Failed to save replay.\n"); return; }
    fprintf(f,"%d\n", h->board_size);
    fprintf(f,"%d\n", h->move_count);
    for(int i=0;i<h->move_count;i++){
        GameMove m = h->moves[i];
        fprintf(f,"%d %d %d %c\n", m.move_number, m.row, m.col, m.player);
    }
    fclose(f);
}

void playReplay(const char* filename){
    FILE* f = fopen(filename,"r");
    if(!f){ printf("Replay file not found.\n"); return; }

    int board_size;
    fscanf(f,"%d", &board_size);

    int** board = createBoard(board_size);
    initializeBoard(board_size, board);

    int move_count;
    fscanf(f,"%d", &move_count);

    printf("\n--- Starting Game Replay ---\n");
    for(int i=0;i<move_count;i++){
        int num,row,col;
        char player;
        fscanf(f,"%d %d %d %c",&num,&row,&col,&player);
        board[row][col] = (player=='X')?1:-1;
        printf("Move %d: Player %c to (%d,%d)\n", num, player, row+1,col+1);
        printBoard(board_size, board);
        printf("\n");
    }
    printf("--- Replay End ---\n");
    freeBoard(board, board_size);
    fclose(f);
}
