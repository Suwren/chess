#ifndef __GAME_H__
#define __GAME_H__

#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include <opencv2/ximgproc.hpp>
#include <opencv2/opencv.hpp>
#include <wiringSerial.h>
#include <wiringPi.h>
#include <string>
#include <unistd.h>
#include "capture.h"
#include "rectget.h"
#include "move.h"
#include <pthread.h>
#include <time.h>
#include<stdio.h>
#define ROW 3
#define COL 3
extern int calx;
extern int caly;
void InitBoard(char board[ROW][COL], int row, int col);

void transfer(int chessmap[9],char board[ROW][COL]);

void Computer_move(char board[ROW][COL], int row, int col);

void transfer5(int chessmap[9],char board[ROW][COL]);

#endif
