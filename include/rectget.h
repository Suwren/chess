//
// Created by lry on 2024/7/14.
//

#ifndef RECTGET_H
#define RECTGET_H

#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include <opencv2/opencv.hpp>
#include "math.h"

using namespace cv;
using namespace std;
using namespace ml;

int blocklocationget(Mat& frame_undistort,Rect dstrect[9]);
void ordermyrect(Mat& framedraw,vector<Rect>& input,Rect dstrect[9]);
void chessget(Mat& frame,Rect dstrect[9],int chessmap [9]);
#endif
