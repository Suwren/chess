#ifndef __GAME_H__
#define __GAME_H__
#define ROW 3
#define COL 3
extern int calx;
extern int caly;
void InitBoard(char board[ROW][COL], int row, int col);

void transfer(int chessmap[9],char board[ROW][COL]);

void Computer_move(char board[ROW][COL], int row, int col);

#endif
