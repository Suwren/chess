//
// Created by lry on 2024/7/14.
//

#ifndef PICTURE_H
#define PICTURE_H

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

void paintchess(int chess[9],int serial);
#endif
