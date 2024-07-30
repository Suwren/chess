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
#include <pthread.h>

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
// 接收32发送的数据
void* uart_rx(void* args)
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
			if(uartbuffer0[0] == 'b')
			{
				while(serialDataAvail(*fd))
				{
					cnt++;
					uartbuffer0[cnt] = serialGetchar(*fd);
				}
				cout << "receive message: " <<uartbuffer0 << endl;
			}
		}
	}
    return 0;
}

int main()
{
	//打印opencv版本
	cout << "OpenCV version : " << CV_VERSION << std::endl;
	//初始化串口
	wiringPiSetup();
	int fd = serialOpen("/dev/ttyS0",115200); //打开串口0
	while(fd==-1)
	{
		cout << "uartopen failed" << endl;
		fd = serialOpen("/dev/ttyS0",115200);
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

	int ret = pthread_create(&tid1, NULL, uart_rx, myuart1);
	if (ret != 0)
	{
		cout << "pthread_create error: error_code=" << ret << endl;
	}
	
	// trackbarinrange(capture);
	 shoot(capture);
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
	//读60张图自动调节白平衡
	for(int i=0;i<60;i++)
	{
		capture >> frame; 
	}
	while(1)
	{
		capture >> frame; 
		while(frame.empty())
		{
			capture >> frame; 
		}
		undistort(frame,frame_undistort,cameraMatrix,distCoeffs);
		bool bgsucess = blocklocationget(frame_undistort,dst_rect);
		// if(bgsucess)
		// {
		// 	//单应性矩阵
		// 	Mat Hm = Mat(3, 3, CV_32FC1, H);
		// 	Mat src_pm = Mat::zeros(3,1,CV_32FC1);
		// 	Mat dst_pm = Mat::zeros(3,1,CV_32FC1);
		// 	// src_pm.at<float>(0,0) = (dst_rect[5].tl().x+dst_rect[5].br().x)/2;
		// 	// src_pm.at<float>(0,1) = (dst_rect[5].tl().y+dst_rect[5].br().y)/2;
		// 	// src_pm.at<float>(0,2) = 1;
		// 	src_pm.at<float>(0,0) = 137;
		// 	src_pm.at<float>(0,1) = 171;
		// 	src_pm.at<float>(0,2) = 1;
		// 	dst_pm = Hm*src_pm;
		// 	cout << dst_pm << endl;
		// }
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
		

		// frame_undistort = frame.clone();
	
		// Point2f AffinePoints0[4] = { Point2f(knn_result[0].x, knn_result[0].y), 
		// Point2f(knn_result[3].x, knn_result[3].y), 
		// Point2f(knn_result[12].x, knn_result[12].y), 
		// Point2f(knn_result[15].x, knn_result[15].y) };
		// Point2f AffinePoints1[4] = { Point2f(150+80, 150), 
		// Point2f(150+80, 630), 
		// Point2f(630+80, 150), 
		// Point2f(630+80, 630) };
		// Trans = getPerspectiveTransform(AffinePoints0, AffinePoints1);
		// warpPerspective(frame_undistort, frame_warp, Trans, Size(frame_undistort.cols-250, frame_undistort.rows));



		char message[50];
		if(missionflag_main!='0')
		{
			cout << "missionflag_main " << missionflag_main << endl;
			strcpy(message,"0");
			switch(missionflag_main)
			{
				case '1':
				{
					//blocklocationget(frame,dst_rect);
					break;
				}
				case '2':
				{
					break;
				}
				case '3':
				{
					break;
				}
				case '4':
				{
					break;
				}
				case '5':
				{
					break;
				}
			}
			missionflag_main = '0';
		}




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
// 	pts_src.push_back(Point2f(137, 109));
// 	pts_src.push_back(Point2f(137, 171));
// 	pts_src.push_back(Point2f(135, 234));
// 	pts_src.push_back(Point2f(134, 295));
// 	pts_src.push_back(Point2f(133, 358));
// 	pts_src.push_back(Point2f(604, 112));
// 	pts_src.push_back(Point2f(604, 175));
// 	pts_src.push_back(Point2f(604, 239));
// 	pts_src.push_back(Point2f(603, 302));
// 	pts_src.push_back(Point2f(603, 366));

// 	// Four corners of the book in destination image. 4个对应点
// 	vector<Point2f> pts_dst;
// 	pts_dst.push_back(Point2f(1899, 1905));
// 	pts_dst.push_back(Point2f(1899, 1650));
// 	pts_dst.push_back(Point2f(1899, 1385));
// 	pts_dst.push_back(Point2f(1899, 1135));
// 	pts_dst.push_back(Point2f(1899, 880));
// 	pts_dst.push_back(Point2f(0, 1945));
// 	pts_dst.push_back(Point2f(0, 1690));
// 	pts_dst.push_back(Point2f(0, 1435));
// 	pts_dst.push_back(Point2f(0, 1180));
// 	pts_dst.push_back(Point2f(0, 925));


// 	Mat h = findHomography(pts_src, pts_dst);
// 	Point3f dst_p;
// 	Point3f src_p;
// 	src_p.x = 604;
// 	src_p.y = 112;
// 	src_p.z = 1;

// 	Mat src_pm=Mat::zeros(3,1,CV_64FC1);
// 	Mat dst_pm=Mat::zeros(3,1,CV_64FC1);
// 	src_pm.at<double>(Point(0,0))=src_p.x;
// 	src_pm.at<double>(Point(1,0))=src_p.y;
// 	src_pm.at<double>(Point(2,0))=src_p.z;
// 	dst_pm = h*src_pm;
// 	cout << h << endl;
// 	waitKey(0);
// 	return 0;
// }