#include "move.h"

int missionFlag = 0;//串口屏给的任务编号
int missionChess = -1;//从串口屏获得的要移动棋子的编号0-9
int rect_code = -1;//从串口屏获得的要移动到的位置编号0-8
int ischessput = 0;//从串口屏获得的人是否落子
int calx=0;
int caly=0;
char board[COL][ROW]={0};

Point chessposition[10]=
{
Point(1899,1905),//0
Point(1899,1650),//1
Point(1899,1385),//2
Point(1899,1135),//3
Point(1899,880),//4
Point(0,1945),//5
Point(0,1690),//6
Point(0,1435),//7
Point(0,1180),//8
Point(0,925)//9
};

void missionStart(VideoCapture capture,int serial)
{
    while(1)
    {
        if(missionFlag==1)
        {mission1(capture,serial);}
        else if(missionFlag==2)
        {mission2(capture,serial);}
        else if(missionFlag==3)
        {mission2(capture,serial);}
        else if(missionFlag==4)
        {mission4(capture,serial);}
        else if(missionFlag==5)
        {mission5(capture,serial);}
    }
    //delay一下
}

void mission1(VideoCapture capture,int serial)
{
    cout << "mission 1 start" << endl;
    
    Mat frame;
    Mat frame_undistort;
    //摄像机内参
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
	Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
    //获取棋子坐标并解算
    Rect dst_rect[9];
    //读60张图自动调节白平衡
	for(int i=0;i<60;i++)
	{
		capture >> frame; 
        //imshow("m1frame",frame);
        waitKey(5);
	}
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
        waitKey(5);
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
    printf("b%04d%04d%04d%04de\r\n",(int)chessposition[missionChess].x,(int)chessposition[missionChess].y,
    (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
    serialPrintf(serial,"b%04d%04d%04d%04de",(int)chessposition[missionChess].x,(int)chessposition[missionChess].y,
    (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
    missionChess = -1;
    missionFlag = 0;
}

void mission2(VideoCapture capture,int serial)
{
    cout << "mission 2 start" << endl;
    
    Mat frame;
    Mat frame_undistort;
    //摄像机内参
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
	Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
    //获取棋子坐标并解算
    Rect dst_rect[9];
    //读60张图自动调节白平衡
	for(int i=0;i<60;i++)
	{
		capture >> frame; 
        //imshow("m1frame",frame);
        waitKey(5);
	}
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
        waitKey(5);
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
        rect_code = -1;
        // cout << dst_pm << endl;
        //发“b棋子x棋子y终点x终点ye”
        while(missionChess==-1){}//等待目标棋子
        printf("b%04d%04d%04d%04de\r\n",(int)chessposition[missionChess].x,(int)chessposition[missionChess].y,
        (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
        serialPrintf(serial,"b%04d%04d%04d%04de",(int)chessposition[missionChess].x,(int)chessposition[missionChess].y,
        (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
        missionChess = -1;
    }
    missionFlag = 0;
}

void mission4(VideoCapture capture,int serial)
{
    cout << "mission 4 start" << endl;
    
    Mat frame;
    Mat frame_undistort;
    //摄像机内参
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
	Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
    //获取棋子坐标并解算
    Rect dst_rect[9];
    //读60张图自动调节白平衡
	for(int i=0;i<60;i++)
	{
		capture >> frame; 
        //imshow("m1frame",frame);
        //waitKey(5);
	}
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
        waitKey(5);
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
    printf("b%04d%04d%04d%04de\r\n",(int)chessposition[missionChess].x,(int)chessposition[missionChess].y,
    (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
    serialPrintf(serial,"b%04d%04d%04d%04de",(int)chessposition[missionChess].x,(int)chessposition[missionChess].y,
    (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
    int num_flag = missionChess;
    missionChess = -1;

    bool ifend = 0;
    int chessmap[9]={0};
    int num = -1;
    while(ifend==0)
    {
        num++;
        if(num == num_flag)
            num++;
        cout << "num" << num << endl;
        while(ischessput==0){}//等待人落子
        ischessput=0;
        //获取地图上棋子的位置
        for(int i=0;i<10;i++)
        {
            capture >> frame; 
        }
        capture >> frame; 
        while(frame.empty())
        {
            capture >> frame; 
        }
        undistort(frame,frame_undistort,cameraMatrix,distCoeffs);    
        chessget(frame_undistort,dst_rect,chessmap);
        //判断棋子是否变动位置，若是，则拿回

        //判断应该朝哪里落子以及是否结束任务
        if(num==4)
            ifend = 1;
        if((chessmap[0]==chessmap[1]&&chessmap[1]==chessmap[2]&&chessmap[2]!=0)||
        (chessmap[3]==chessmap[4]&&chessmap[4]==chessmap[5]&&chessmap[5]!=0)||
        (chessmap[6]==chessmap[7]&&chessmap[7]==chessmap[8]&&chessmap[8]!=0)||
        (chessmap[0]==chessmap[3]&&chessmap[3]==chessmap[6]&&chessmap[6]!=0)||
        (chessmap[1]==chessmap[4]&&chessmap[4]==chessmap[7]&&chessmap[7]!=0)||
        (chessmap[2]==chessmap[5]&&chessmap[5]==chessmap[8]&&chessmap[8]!=0)||
        (chessmap[0]==chessmap[4]&&chessmap[4]==chessmap[8]&&chessmap[8]!=0)||
        (chessmap[2]==chessmap[4]&&chessmap[4]==chessmap[6]&&chessmap[6]!=0))
            ifend = 1;
        //rect_code-位置坐标 missionChess-目标棋子
        InitBoard(board,3,3);
        transfer(chessmap,board);
        Computer_move(board,3,3);
        int rect_code = 3*caly+calx;
        src_pm.at<float>(0,0) = (dst_rect[rect_code].tl().x+dst_rect[rect_code].br().x)/2;
        src_pm.at<float>(0,1) = (dst_rect[rect_code].tl().y+dst_rect[rect_code].br().y)/2;
        src_pm.at<float>(0,2) = 1;
        dst_pm = Hm*src_pm;
        rect_code = -1;
        //落子并且清空位置信息
        // while(missionChess==-1){}//等待目标棋子
        printf("b%04d%04d%04d%04de\r\n",(int)chessposition[num].x,(int)chessposition[num].y,
        (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
        serialPrintf(serial,"b%04d%04d%04d%04de",(int)chessposition[num].x,(int)chessposition[num].y,
        (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
        missionChess = -1;
    }
    missionFlag = 0;
}

void mission5(VideoCapture capture,int serial)
{
    cout << "mission 5 start" << endl;
    
    Mat frame;
    Mat frame_undistort;
    //摄像机内参
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
	Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
    //获取棋子坐标并解算
    Rect dst_rect[9];
    //读60张图自动调节白平衡
	for(int i=0;i<60;i++)
	{
		capture >> frame; 
        //imshow("m1frame",frame);
        //waitKey(5);
	}
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
        waitKey(5);
    }

    //单应性矩阵
    Mat Hm = Mat(3, 3, CV_32FC1, H);
    Mat src_pm = Mat::zeros(3,1,CV_32FC1);
    Mat dst_pm = Mat::zeros(3,1,CV_32FC1);

    bool ifend = 0;
    int chessmap[9]={0};
    int num = 4;
    while(ifend==0)
    {
        num++;
        cout << "num" << num << endl;
        while(ischessput==0){}//等待人落子
        ischessput=0;
        //获取地图上棋子的位置
        for(int i=0;i<10;i++)
        {
            capture >> frame; 
        }
        capture >> frame; 
        while(frame.empty())
        {
            capture >> frame; 
        }
        undistort(frame,frame_undistort,cameraMatrix,distCoeffs);    
        chessget(frame_undistort,dst_rect,chessmap);
        //判断棋子是否变动位置，若是，则拿回

        //判断应该朝哪里落子以及是否结束任务
        if(num==9)
            ifend = 1;
        if((chessmap[0]==chessmap[1]&&chessmap[1]==chessmap[2]&&chessmap[2]!=0)||
        (chessmap[3]==chessmap[4]&&chessmap[4]==chessmap[5]&&chessmap[5]!=0)||
        (chessmap[6]==chessmap[7]&&chessmap[7]==chessmap[8]&&chessmap[8]!=0)||
        (chessmap[0]==chessmap[3]&&chessmap[3]==chessmap[6]&&chessmap[6]!=0)||
        (chessmap[1]==chessmap[4]&&chessmap[4]==chessmap[7]&&chessmap[7]!=0)||
        (chessmap[2]==chessmap[5]&&chessmap[5]==chessmap[8]&&chessmap[8]!=0)||
        (chessmap[0]==chessmap[4]&&chessmap[4]==chessmap[8]&&chessmap[8]!=0)||
        (chessmap[2]==chessmap[4]&&chessmap[4]==chessmap[6]&&chessmap[6]!=0))
            ifend = 1;
        //rect_code-位置坐标 missionChess-目标棋子
        InitBoard(board,3,3);
        transfer(chessmap,board);
        Computer_move(board,3,3);
        int rect_code = 3*caly+calx;
        src_pm.at<float>(0,0) = (dst_rect[rect_code].tl().x+dst_rect[rect_code].br().x)/2;
        src_pm.at<float>(0,1) = (dst_rect[rect_code].tl().y+dst_rect[rect_code].br().y)/2;
        src_pm.at<float>(0,2) = 1;
        dst_pm = Hm*src_pm;
        rect_code = -1;
        //落子并且清空位置信息
        // while(missionChess==-1){}//等待目标棋子
        printf("b%04d%04d%04d%04de\r\n",(int)chessposition[num].x,(int)chessposition[num].y,
        (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
        serialPrintf(serial,"b%04d%04d%04d%04de",(int)chessposition[num].x,(int)chessposition[num].y,
        (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
        missionChess = -1;
    }
    missionFlag = 0;
}

//提高，若人多落子，拿回