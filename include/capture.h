//
// Created by lry on 2024/7/14.
//

#ifndef CAPTURE_H
#define CAPTURE_H

#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include <opencv2/opencv.hpp>

#define Frame_WIDTH 1280
#define Frame_HEIGHT 720

using namespace cv;
using namespace std;

extern float cm[3][3];//摄像头内参矩阵
extern float dc[1][5];//畸变矩阵
extern float H[3][3];

void capinit(VideoCapture &capture);
void shoot(VideoCapture &capture);
void capcalibrate(VideoCapture &capture);
void trackbarinrange(VideoCapture &capture);
#endif
