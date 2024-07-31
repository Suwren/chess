//
// Created by lry on 2024/7/14.
//

#ifndef MOVE_H
#define MOVE_H

#include <iostream>
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
#include "game.h"

using namespace cv;
using namespace std;
using namespace ml;

extern int missionFlag;//串口屏给的任务编号
extern int missionChess;//从串口屏获得的要移动棋子的编号0-9
extern int rect_code;//从串口屏获得的要移动到的位置编号0-8
extern int ischessput;//从串口屏获得的人是否落子
extern int exitinput;//从串口屏获得的任务是否被终端
void missionStart(VideoCapture capture,int serial,int tft_serial);
void mission1(VideoCapture capture,int serial,int tft_serial);
void mission2(VideoCapture capture,int serial,int tft_serial);
void mission4(VideoCapture capture,int serial,int tft_serial);
void mission5(VideoCapture capture,int serial,int tft_serial);
#endif
