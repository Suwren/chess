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
#include <time.h>

using namespace cv;
using namespace ml;
using namespace std;


double t1=0,t2=0,spendTime=0;
int FPS=0;
Mat frameforshow;
char bytebuffer0;
char uartbuffer0[40] = {'0'};

pthread_mutex_t msthreadmutex;
char missionflag_thread = '0';
char missionflag_main = '0';
// 线程的运行函数
// 接收串口屏发送的数据
void* tft_rx(void* args)
{
	int* fd = NULL;
	fd=(int*)args;
	int cnt;
	while(1)
	{	
		if(serialDataAvail(*fd))
		{
			cnt = 0; 
			memset(uartbuffer0,0,sizeof(uartbuffer0));
			uartbuffer0[0] = serialGetchar(*fd);
			if(uartbuffer0[0] == 'm')
			{
				while(serialDataAvail(*fd))
				{
					cnt++;
					uartbuffer0[cnt] = serialGetchar(*fd);
					//cout << "receive " << uartbuffer0[cnt] << endl;
				}
				cout << "receive message: " <<uartbuffer0 << endl;
				missionFlag = uartbuffer0[1]-'0';
				missionChess = uartbuffer0[3]-'0';
				rect_code = uartbuffer0[5]-'0';
				ischessput = uartbuffer0[7]-'0';	
			}
		}
		// sleep(5);
	}
    return 0;
}

int main()
{
	//打印opencv版本
	cout << "OpenCV version : " << CV_VERSION << std::endl;
	//初始化串口
	wiringPiSetup();
	int fd = serialOpen("/dev/ttyS4",9600); //打开串口4
	while(fd==-1)
	{
		cout << "uartopen failed" << endl;
		fd = serialOpen("/dev/ttyS4",9600);
	}

	int fd2 = serialOpen("/dev/ttyS0",115200); //打开串口0
	while(fd2==-1)
	{
		cout << "uartopen failed" << endl;
		fd2 = serialOpen("/dev/ttyS0",115200);
	}
	int* myuart1=&fd;

	//初始化摄像头
	VideoCapture capture(0,CAP_V4L2);
	if (!capture.isOpened()) 
	{
		cout << "open camera failed. " << endl;
		return -1;
	}
	capinit(capture);
	// 创建并打开线程
	pthread_t tid1;

	int ret = pthread_create(&tid1, NULL, tft_rx, myuart1);
	if (ret != 0)
	{
		cout << "pthread_create error: error_code=" << ret << endl;
	}

	// trackbarinrange(capture);
	// shoot(capture);
	// capcalibrate(capture);

	Mat frame;
	Mat frame_undistort;
	Mat frame_warp;
	Mat Trans;
	//摄像机内参
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
	Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
	//9个区块位置
	Rect dst_rect[9];
	//9个区块棋子状态
	int chessmap[9];
	
	while(1)
	{
		// capture >> frame; 
		// while(frame.empty())
		// {
		// 	capture >> frame; 
		// }
		// undistort(frame,frame_undistort,cameraMatrix,distCoeffs);
		// bool bgsucess = blocklocationget(frame_undistort,dst_rect);
		// if(bgsucess)
		// {
		// 	waitKey(10000);
		// 	for(int i=0;i<60;i++)
		// 	{
		// 		capture >> frame; 
		// 	}
		// 	undistort(frame,frame_undistort,cameraMatrix,distCoeffs);
		// 	chessget(frame_undistort,dst_rect,chessmap);
		// }
		missionStart(capture,fd2);




		// 	waitKey(1);
		// 	t2 = getTickCount();
		// 	spendTime = ( t2 - t1 ) /  (getTickFrequency());
		// 	FPS = FPS*0.9+0.1 / spendTime;
		// 	//printf("FPS = %d\r\n" , FPS);	
	}

	pthread_exit(NULL);
	return 0;
}


// //用于标定相机坐标到机器坐标
// int main(int argc, char** argv)
// {

// 	vector<Point2f> pts_src;
// 	pts_src.push_back(Point2f(261, 186));
// 	pts_src.push_back(Point2f(264, 540));
// 	pts_src.push_back(Point2f(930, 205));
// 	pts_src.push_back(Point2f(936, 558));


// 	// Four corners of the book in destination image. 4个对应点
// 	vector<Point2f> pts_dst;
// 	pts_dst.push_back(Point2f(1899, 1905));
// 	pts_dst.push_back(Point2f(1899, 880));
// 	pts_dst.push_back(Point2f(0, 1945));
// 	pts_dst.push_back(Point2f(0, 925));



// 	Mat h = findHomography(pts_src, pts_dst);
// 	Point3f dst_p;
// 	Point3f src_p;
// 	src_p.x = 261;
// 	src_p.y = 186;
// 	src_p.z = 1;

// 	Mat src_pm=Mat::zeros(3,1,CV_64FC1);
// 	Mat dst_pm=Mat::zeros(3,1,CV_64FC1);
// 	src_pm.at<double>(Point(0,0))=src_p.x;
// 	src_pm.at<double>(Point(1,0))=src_p.y;
// 	src_pm.at<double>(Point(2,0))=src_p.z;
// 	dst_pm = h*src_pm;
// 	cout << h << endl;
// 	cout << dst_pm << endl;

// 	waitKey(0);
// 	return 0;
// }

