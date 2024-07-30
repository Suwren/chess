#include "move.h"
int missionFlag = 0;//串口屏给的任务编号
int missionChess = -1;//从串口屏获得的要移动棋子的编号0-9
int rect_code = -1;//从串口屏获得的要移动到的位置编号0-8
int ischessput = 0;//从串口屏获得的人是否落子


Point chessposition[10]=
{
Point(),//0
Point(),//1
Point(),//2
Point(),//3
Point(),//4
Point(),//5
Point(),//6
Point(),//7
Point(),//8
Point()//9
};

void missisonStart()
{
    while(1)
    {
        if(missionFlag==1)
        {mission1();missionFlag=0;}
        else if(missionFlag==2)
        {mission2();missionFlag=0;}
        else if(missionFlag==3)
        {mission2();missionFlag=0;}
        else if(missionFlag==4)
        {mission4();missionFlag=0;}
        else if(missionFlag==5)
        {mission5();missionFlag=0;}
    }
    //delay一下
}

void mission1(VideoCapture capture,int serial)
{
    Mat frame;
    Mat frame_undistort;
    //摄像机内参
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
	Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
    //获取棋子坐标并解算
    Rect dst_rect[9];
    capture >> frame; 
    while(frame.empty())
    {
        capture >> frame; 
    }
    undistort(frame,frame_undistort,cameraMatrix,distCoeffs);
    bool bgsucess = blocklocationget(frame_undistort,dst_rect);
    while(!bgsucess)
    {
        bgsucess = blocklocationget(frame_undistort,dst_rect);
    }

    //单应性矩阵
    Mat Hm = Mat(3, 3, CV_32FC1, H);
    Mat src_pm = Mat::zeros(3,1,CV_32FC1);
    Mat dst_pm = Mat::zeros(3,1,CV_32FC1);

    //解算位置坐标
    while(rect_code==-1){}//等待位置坐标
    src_pm.at<float>(0,0) = (dst_rect[rect_code].tl().x+dst_rect[rect_code].br().x)/2;
    src_pm.at<float>(0,1) = (dst_rect[rect_code].tl().y+dst_rect[rect_code].br().y)/2;
    src_pm.at<float>(0,2) = 1;
    dst_pm = Hm*src_pm;
    rect_code = -1;
    // cout << dst_pm << endl;
    //直接给我发“b棋子x棋子y终点x终点ye”
    while(missionChess==-1){}//等待目标棋子
    serialPrintf(serial,"b%d%f%f%f%fe",missionChess,(int)chessposition[missionChess].x,(int)chessposition[missionChess].y,
    (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
    missionChess = -1;
}

void missison2(VideoCapture capture,int serial)
{
    Mat frame;
    Mat frame_undistort;
    //摄像机内参
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
	Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
    //获取棋子坐标并解算
    Rect dst_rect[9];

    capture >> frame; 
    while(frame.empty())
    {
        capture >> frame; 
    }
    undistort(frame,frame_undistort,cameraMatrix,distCoeffs);
    bool bgsucess = blocklocationget(frame_undistort,dst_rect);
    while(!bgsucess)
    {
        capture >> frame; 
        while(frame.empty())
        {
            capture >> frame; 
        }
        undistort(frame,frame_undistort,cameraMatrix,distCoeffs);
        bgsucess = blocklocationget(frame_undistort,dst_rect);
    }

    //单应性矩阵
    Mat Hm = Mat(3, 3, CV_32FC1, H);
    Mat src_pm = Mat::zeros(3,1,CV_32FC1);
    Mat dst_pm = Mat::zeros(3,1,CV_32FC1);

    //解算位置坐标
    for(int i=0;i<4;i++)
    {
        while(rect_code==-1){}//等待位置坐标
        src_pm.at<float>(0,0) = (dst_rect[rect_code].tl().x+dst_rect[rect_code].br().x)/2;
        src_pm.at<float>(0,1) = (dst_rect[rect_code].tl().y+dst_rect[rect_code].br().y)/2;
        src_pm.at<float>(0,2) = 1;
        dst_pm = Hm*src_pm;
        rect_code = -1
        // cout << dst_pm << endl;
        //发“b棋子x棋子y终点x终点ye”
        while(missionChess==-1){}//等待目标棋子
        serialPrintf(serial,"b%d%f%f%f%fe",missionChess,(int)chessposition[missionChess].x,(int)chessposition[missionChess].y,
        (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
        missionChess = -1;
    }

}

void missison4(VideoCapture capture,int serial)
{
    Mat frame;
    Mat frame_undistort;
    //摄像机内参
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
	Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
    //获取棋子坐标并解算
    Rect dst_rect[9];

    capture >> frame; 
    while(frame.empty())
    {
        capture >> frame; 
    }
    undistort(frame,frame_undistort,cameraMatrix,distCoeffs);
    bool bgsucess = blocklocationget(frame_undistort,dst_rect);
    while(!bgsucess)
    {
        capture >> frame; 
        while(frame.empty())
        {
            capture >> frame; 
        }
        undistort(frame,frame_undistort,cameraMatrix,distCoeffs);
        bgsucess = blocklocationget(frame_undistort,dst_rect);
    }

    //单应性矩阵
    Mat Hm = Mat(3, 3, CV_32FC1, H);
    Mat src_pm = Mat::zeros(3,1,CV_32FC1);
    Mat dst_pm = Mat::zeros(3,1,CV_32FC1);

    //串口屏指令装置执黑棋先落子
    while(rect_code==-1){}//等待位置坐标
    src_pm.at<float>(0,0) = (dst_rect[rect_code].tl().x+dst_rect[rect_code].br().x)/2;
    src_pm.at<float>(0,1) = (dst_rect[rect_code].tl().y+dst_rect[rect_code].br().y)/2;
    src_pm.at<float>(0,2) = 1;
    dst_pm = Hm*src_pm;
    rect_code = -1;
    // cout << dst_pm << endl;
    //发“b棋子x棋子y终点x终点ye”
    while(missionChess==-1){}//等待目标棋子
    serialPrintf(serial,"b%d%f%f%f%fe",missionChess,(int)chessposition[missionChess].x,(int)chessposition[missionChess].y,
    (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
    missionChess = -1;

    bool ifsucess = 0;
    int chessmap[9]={0};
    while(ifsucess==0)
    {
        while(ischessput==0){}//等待人落子
        //获取地图上棋子的位置
        
        capture >> frame; 
        while(frame.empty())
        {
            capture >> frame; 
        }
        undistort(frame,frame_undistort,cameraMatrix,distCoeffs);
        chessget(frame_undistort,dst_rect,chessmap);
        //判断棋子是否变动位置，若是，则拿回

        //判断应该朝哪里落子以及是否胜利
        //rect_code-位置坐标 missionChess-目标棋子

        //落子并且清空位置信息
        serialPrintf(serial,"b%d%f%f%f%fe",missionChess,(int)chessposition[missionChess].x,(int)chessposition[missionChess].y,
        (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
        rect_code = -1;
        missionChess = -1;
    }
}

void missison5(VideoCapture capture,int serial)
{
    Mat frame;
    Mat frame_undistort;
    //摄像机内参
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
	Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
    //获取棋子坐标并解算
    Rect dst_rect[9];

    capture >> frame; 
    while(frame.empty())
    {
        capture >> frame; 
    }
    undistort(frame,frame_undistort,cameraMatrix,distCoeffs);
    bool bgsucess = blocklocationget(frame_undistort,dst_rect);
    while(!bgsucess)
    {
        capture >> frame; 
        while(frame.empty())
        {
            capture >> frame; 
        }
        undistort(frame,frame_undistort,cameraMatrix,distCoeffs);
        bgsucess = blocklocationget(frame_undistort,dst_rect);
    }

    //单应性矩阵
    Mat Hm = Mat(3, 3, CV_32FC1, H);
    Mat src_pm = Mat::zeros(3,1,CV_32FC1);
    Mat dst_pm = Mat::zeros(3,1,CV_32FC1);

    bool ifsucess = 0;
    int chessmap[9]={0};
    while(ifsucess==0)
    {
        while(ischessput==0){}//等待人落子
        //获取地图上棋子的位置
        capture >> frame; 
        while(frame.empty())
        {
            capture >> frame; 
        }
        undistort(frame,frame_undistort,cameraMatrix,distCoeffs);
        chessget(frame_undistort,dst_rect,chessmap);
        //判断棋子是否变动位置，若是，则拿回

        //判断应该朝哪里落子以及是否胜利
        //rect_code-位置坐标 missionChess-目标棋子
        
        //落子并且清空位置信息
        serialPrintf(serial,"b%d%f%f%f%fe",missionChess,(int)chessposition[missionChess].x,(int)chessposition[missionChess].y,
        (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
        rect_code = -1;
        missionChess = -1;
    }
}

//提高，若人多落子，拿回