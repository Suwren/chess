#include "move.h"
#include "picture.h"

int missionFlag = 0;//串口屏给的任务编号
int missionChess = -1;//从串口屏获得的要移动棋子的编号0-9
int rect_code = -1;//从串口屏获得的要移动到的位置编号0-8
int ischessput = 0;//从串口屏获得的人是否落子
int exitinput = 0;

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

void putintomap(int& rect_code,int& missionChess,Rect dst_rect[9],Point chessposition[10],int serial)
{
    //单应性矩阵
    Mat Hm = Mat(3, 3, CV_32FC1, H);
    Mat src_pm = Mat::zeros(3,1,CV_32FC1);
    Mat dst_pm = Mat::zeros(3,1,CV_32FC1);
    //机器落子 
    src_pm.at<float>(0,0) = (dst_rect[rect_code].tl().x+dst_rect[rect_code].br().x)/2;
    src_pm.at<float>(0,1) = (dst_rect[rect_code].tl().y+dst_rect[rect_code].br().y)/2;
    src_pm.at<float>(0,2) = 1;
    dst_pm = Hm*src_pm;
    rect_code = -1;
    // cout << dst_pm << endl;
    //发“b棋子x棋子y终点x终点ye”
    printf("b%04d%04d%04d%04de\r\n",(int)chessposition[missionChess].x,(int)chessposition[missionChess].y,
    (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
    serialPrintf(serial,"b%04d%04d%04d%04de",(int)chessposition[missionChess].x,(int)chessposition[missionChess].y,
    (int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1));
    missionChess = -1;
}




void missionStart(VideoCapture capture,int serial,int tft_serial)
{
    while(1)
    {
        if(missionFlag==1)
        {mission1(capture,serial,tft_serial);}
        else if(missionFlag==2)
        {mission2(capture,serial,tft_serial);}
        else if(missionFlag==3)
        {mission2(capture,serial,tft_serial);}
        else if(missionFlag==4)
        {mission4(capture,serial,tft_serial);}
        else if(missionFlag==5)
        {mission5(capture,serial,tft_serial);}
    }
    //delay一下
}





void mission1(VideoCapture capture,int serial,int tft_serial)
{
    cout << "mission 1 start" << endl;
    
    Mat frame;
    Mat frame_undistort;
    //摄像机内参
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
	Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
    //获取棋子坐标并解算
    Rect dst_rect[9];
    //读10张图自动调节白平衡
	for(int i=0;i<10;i++)
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





void mission2(VideoCapture capture,int serial,int tft_serial)
{
    cout << "mission 2 start" << endl;
    
    Mat frame;
    Mat frame_undistort;
    //摄像机内参
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
	Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
    //获取棋子坐标并解算
    Rect dst_rect[9];
    //读10张图自动调节白平衡
	for(int i=0;i<10;i++)
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
        //waitKey(5);
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





void mission4(VideoCapture capture,int serial,int tft_serial)
{
    cout << "mission 4 start" << endl;

    Mat frame;
    Mat frame_undistort;
    //摄像机内参
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
	Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
    //获取棋子坐标并解算
    Rect dst_rect[9];
    //读10张图自动调节白平衡
	for(int i=0;i<10;i++)
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

    //创建空的地图
    int chessmap[9]={0};
    int num = -1;
    int num_flag = -1;
    
    int lastchessmap[9];
    for(int k = 0;k<9;k++)
    {
        lastchessmap[k]=0;
    }

    //机器落子
    while(rect_code==-1){}//等待位置坐标
    while(missionChess==-1){}//等待目标棋子
    num_flag = missionChess;
    chessmap[rect_code]=1;
    lastchessmap[rect_code]=1;
    putintomap(rect_code,missionChess,dst_rect,chessposition,serial);
    paintchess(chessmap,tft_serial);

    while(1)
    {
        num++;
        if(num==num_flag)
            num++;
        cout << "num" << num << endl;
        //等待人落子    
        while(ischessput==0)
        {
            if(exitinput)
                break;
        }
        if(exitinput)
        {
            break;
            exitinput = 0;
        }
                
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
        paintchess(chessmap,tft_serial);
        ischessput=0;
        //判断棋子是否变动位置，若是，则拿回
        int oldplace;
        int newplace;
        oldplace = -1;
        newplace = -1;
        for(int k = 0;k<9;k++)
        {
            if(lastchessmap[k]!=chessmap[k]&&chessmap[k]==1)
            {
                newplace=k;
            }
            if(lastchessmap[k]!=chessmap[k]&&lastchessmap[k]==1)
            {
                oldplace=k;
            }
        }
        //判断棋子是否连放两个
        int humanput;
        humanput = -1;
        int putflag[3];
        for(int k = 0;k<9;k++)
        {
            if(lastchessmap[k]!=chessmap[k]&&chessmap[k]==2)
            {
                humanput++;
                putflag[humanput] = k;
            }
        }
        if(oldplace!=-1&&newplace!=-1)
        {
            num--;
            src_pm.at<float>(0,0) = (dst_rect[newplace].tl().x+dst_rect[newplace].br().x)/2;
            src_pm.at<float>(0,1) = (dst_rect[newplace].tl().y+dst_rect[newplace].br().y)/2;
            src_pm.at<float>(0,2) = 1;
            Mat dst_pm_new = Hm*src_pm;
            src_pm.at<float>(0,0) = (dst_rect[oldplace].tl().x+dst_rect[oldplace].br().x)/2;
            src_pm.at<float>(0,1) = (dst_rect[oldplace].tl().y+dst_rect[oldplace].br().y)/2;
            src_pm.at<float>(0,2) = 1;
            Mat dst_pm_old = Hm*src_pm;
            printf("b%04d%04d%04d%04de\r\n",(int)dst_pm_new.at<float>(0,0),(int)dst_pm_new.at<float>(0,1),
            (int)dst_pm_old.at<float>(0,0),(int)dst_pm_old.at<float>(0,1));
            serialPrintf(serial,"b%04d%04d%04d%04de",(int)dst_pm_new.at<float>(0,0),(int)dst_pm_new.at<float>(0,1),
            (int)dst_pm_old.at<float>(0,0),(int)dst_pm_old.at<float>(0,1));
            waitKey(9000);
            for(int k = 0;k<9;k++)
            {
                chessmap[k]=lastchessmap[k];
            }
            paintchess(chessmap,tft_serial);
        }
        else if(humanput >= 2)
        {
            num--;
            for(int k = 0;k<sizeof(putflag);k++)
            {
                src_pm.at<float>(0,0) = (dst_rect[putflag[k]].tl().x+dst_rect[putflag[k]].br().x)/2;
                src_pm.at<float>(0,1) = (dst_rect[putflag[k]].tl().y+dst_rect[putflag[k]].br().y)/2;
                src_pm.at<float>(0,2) = 1;
                Mat dst_pm = Hm*src_pm;
                printf("b%04d%04d%04d%04de\r\n",(int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1),
                3600,1000);
                serialPrintf(serial,"b%04d%04d%04d%04de",(int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1),
                3600,1000);
                waitKey(1500);
            }
            for(int k = 0;k<9;k++)
            {
                chessmap[k]=lastchessmap[k];
            }
            paintchess(chessmap,tft_serial);
        }
        else
        {
            //判断是否结束任务
            if((chessmap[0]==chessmap[1]&&chessmap[1]==chessmap[2]&&chessmap[2]!=0)||
            (chessmap[3]==chessmap[4]&&chessmap[4]==chessmap[5]&&chessmap[5]!=0)||
            (chessmap[6]==chessmap[7]&&chessmap[7]==chessmap[8]&&chessmap[8]!=0)||
            (chessmap[0]==chessmap[3]&&chessmap[3]==chessmap[6]&&chessmap[6]!=0)||
            (chessmap[1]==chessmap[4]&&chessmap[4]==chessmap[7]&&chessmap[7]!=0)||
            (chessmap[2]==chessmap[5]&&chessmap[5]==chessmap[8]&&chessmap[8]!=0)||
            (chessmap[0]==chessmap[4]&&chessmap[4]==chessmap[8]&&chessmap[8]!=0)||
            (chessmap[2]==chessmap[4]&&chessmap[4]==chessmap[6]&&chessmap[6]!=0))
                break;
            if(num==5)
                break;
            //rect_code-位置坐标 missionChess-目标棋子
            //解算下一步位置
            InitBoard(board,3,3);
            transfer(chessmap,board);
            Computer_move(board,3,3);
            int rect_code = 3*calx+caly;
            cout << "mission4 rect_code" << rect_code << endl;
            //更新地图信息
            chessmap[rect_code]=1;
            int num_;
            num_ = num;
            putintomap(rect_code,num_,dst_rect,chessposition,serial);
            waitKey(9000);
            paintchess(chessmap,tft_serial);
            for(int k = 0;k<9;k++)
            {
                lastchessmap[k]=chessmap[k];
            }
            //判断是否结束任务
            if((lastchessmap[0]==lastchessmap[1]&&lastchessmap[1]==lastchessmap[2]&&lastchessmap[2]!=0)||
            (lastchessmap[3]==lastchessmap[4]&&lastchessmap[4]==lastchessmap[5]&&lastchessmap[5]!=0)||
            (lastchessmap[6]==lastchessmap[7]&&lastchessmap[7]==lastchessmap[8]&&lastchessmap[8]!=0)||
            (lastchessmap[0]==lastchessmap[3]&&lastchessmap[3]==lastchessmap[6]&&lastchessmap[6]!=0)||
            (lastchessmap[1]==lastchessmap[4]&&lastchessmap[4]==lastchessmap[7]&&lastchessmap[7]!=0)||
            (lastchessmap[2]==lastchessmap[5]&&lastchessmap[5]==lastchessmap[8]&&lastchessmap[8]!=0)||
            (lastchessmap[0]==lastchessmap[4]&&lastchessmap[4]==lastchessmap[8]&&lastchessmap[8]!=0)||
            (lastchessmap[2]==lastchessmap[4]&&lastchessmap[4]==lastchessmap[6]&&lastchessmap[6]!=0))
                break;
        }
    }
    serialPrintf(tft_serial, "b1.bco=1024");
    serialPutchar(tft_serial,0xff);
    serialPutchar(tft_serial,0xff);
    serialPutchar(tft_serial,0xff);
    missionFlag = 0;
}





void mission5(VideoCapture capture,int serial,int tft_serial)
{
    cout << "mission 5 start" << endl;

    Mat frame;
    Mat frame_undistort;
    //摄像机内参
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
	Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
    //获取棋子坐标并解算
    Rect dst_rect[9];
    //读10张图自动调节白平衡
	for(int i=0;i<10;i++)
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

    //创建空的地图
    int chessmap[9]={0};
    int num = -1;
    int num_flag = -1;
    
    int lastchessmap[9];
    for(int k = 0;k<9;k++)
    {
        lastchessmap[k]=0;
    }

    num = 4;
    while(1)
    {
        num++;
        // if(num==num_flag)
        //     num++;
        cout << "num" << num << endl;
        //等待人落子    
        while(ischessput==0)
        {
            if(exitinput)
                break;
        }
        if(exitinput)
        {
            break;
            exitinput = 0;
        }

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
        paintchess(chessmap,tft_serial);
        ischessput=0;
        //判断棋子是否变动位置，若是，则拿回
        int oldplace;
        int newplace;
        oldplace = -1;
        newplace = -1;
        for(int k = 0;k<9;k++)
        {
            if(lastchessmap[k]!=chessmap[k]&&chessmap[k]==2)
            {
                newplace=k;
            }
            if(lastchessmap[k]!=chessmap[k]&&lastchessmap[k]==2)
            {
                oldplace=k;
            }
        }
        //判断棋子是否连放两个，若是则丢掉（3300,1600）
        int humanput;
        humanput = -1;
        int putflag[3];
        for(int k = 0;k<9;k++)
        {
            if(lastchessmap[k]!=chessmap[k]&&chessmap[k]==1)
            {
                humanput++;
                putflag[humanput] = k;
            }
        }
        if(oldplace!=-1&&newplace!=-1)
        {
            num--;
            src_pm.at<float>(0,0) = (dst_rect[newplace].tl().x+dst_rect[newplace].br().x)/2;
            src_pm.at<float>(0,1) = (dst_rect[newplace].tl().y+dst_rect[newplace].br().y)/2;
            src_pm.at<float>(0,2) = 1;
            Mat dst_pm_new = Hm*src_pm;
            src_pm.at<float>(0,0) = (dst_rect[oldplace].tl().x+dst_rect[oldplace].br().x)/2;
            src_pm.at<float>(0,1) = (dst_rect[oldplace].tl().y+dst_rect[oldplace].br().y)/2;
            src_pm.at<float>(0,2) = 1;
            Mat dst_pm_old = Hm*src_pm;
            printf("b%04d%04d%04d%04de\r\n",(int)dst_pm_new.at<float>(0,0),(int)dst_pm_new.at<float>(0,1),
            (int)dst_pm_old.at<float>(0,0),(int)dst_pm_old.at<float>(0,1));
            serialPrintf(serial,"b%04d%04d%04d%04de",(int)dst_pm_new.at<float>(0,0),(int)dst_pm_new.at<float>(0,1),
            (int)dst_pm_old.at<float>(0,0),(int)dst_pm_old.at<float>(0,1));
            waitKey(9000);
            for(int k = 0;k<9;k++)
            {
                chessmap[k]=lastchessmap[k];
            }
            paintchess(chessmap,tft_serial);
        }
        else if(humanput >= 2)
        {
            num--;
            for(int k = 0;k<sizeof(putflag);k++)
            {
                src_pm.at<float>(0,0) = (dst_rect[putflag[k]].tl().x+dst_rect[putflag[k]].br().x)/2;
                src_pm.at<float>(0,1) = (dst_rect[putflag[k]].tl().y+dst_rect[putflag[k]].br().y)/2;
                src_pm.at<float>(0,2) = 1;
                Mat dst_pm = Hm*src_pm;
                printf("b%04d%04d%04d%04de\r\n",(int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1),
                3600,1000);
                serialPrintf(serial,"b%04d%04d%04d%04de",(int)dst_pm.at<float>(0,0),(int)dst_pm.at<float>(0,1),
                3600,1000);
                waitKey(1500);
            }
            for(int k = 0;k<9;k++)
            {
                chessmap[k]=lastchessmap[k];
            }
            paintchess(chessmap,tft_serial);
        }
        else
        {
            //判断是否结束任务
            if((chessmap[0]==chessmap[1]&&chessmap[1]==chessmap[2]&&chessmap[2]!=0)||
            (chessmap[3]==chessmap[4]&&chessmap[4]==chessmap[5]&&chessmap[5]!=0)||
            (chessmap[6]==chessmap[7]&&chessmap[7]==chessmap[8]&&chessmap[8]!=0)||
            (chessmap[0]==chessmap[3]&&chessmap[3]==chessmap[6]&&chessmap[6]!=0)||
            (chessmap[1]==chessmap[4]&&chessmap[4]==chessmap[7]&&chessmap[7]!=0)||
            (chessmap[2]==chessmap[5]&&chessmap[5]==chessmap[8]&&chessmap[8]!=0)||
            (chessmap[0]==chessmap[4]&&chessmap[4]==chessmap[8]&&chessmap[8]!=0)||
            (chessmap[2]==chessmap[4]&&chessmap[4]==chessmap[6]&&chessmap[6]!=0))
                break;
            if(num==9)
                break;
            //rect_code-位置坐标 missionChess-目标棋子
            //解算下一步位置
            InitBoard(board,3,3);
            transfer5(chessmap,board);
            Computer_move(board,3,3);
            int rect_code = 3*calx+caly;
            cout << "mission4 rect_code" << rect_code << endl;
            //更新地图信息
            chessmap[rect_code]=2;
            int num_;
            num_ = num;
            putintomap(rect_code,num_,dst_rect,chessposition,serial);
            waitKey(9000);
            paintchess(chessmap,tft_serial);
            for(int k = 0;k<9;k++)
            {
                lastchessmap[k]=chessmap[k];
            }
            //判断是否结束任务
            if((chessmap[0]==chessmap[1]&&chessmap[1]==chessmap[2]&&chessmap[2]!=0)||
            (chessmap[3]==chessmap[4]&&chessmap[4]==chessmap[5]&&chessmap[5]!=0)||
            (chessmap[6]==chessmap[7]&&chessmap[7]==chessmap[8]&&chessmap[8]!=0)||
            (chessmap[0]==chessmap[3]&&chessmap[3]==chessmap[6]&&chessmap[6]!=0)||
            (chessmap[1]==chessmap[4]&&chessmap[4]==chessmap[7]&&chessmap[7]!=0)||
            (chessmap[2]==chessmap[5]&&chessmap[5]==chessmap[8]&&chessmap[8]!=0)||
            (chessmap[0]==chessmap[4]&&chessmap[4]==chessmap[8]&&chessmap[8]!=0)||
            (chessmap[2]==chessmap[4]&&chessmap[4]==chessmap[6]&&chessmap[6]!=0))
                break;
        }
    }
    serialPrintf(tft_serial, "b1.bco=1024");
    serialPutchar(tft_serial,0xff);
    serialPutchar(tft_serial,0xff);
    serialPutchar(tft_serial,0xff);
    missionFlag = 0;
}






//提高，若人多落子，拿回                                                                                                                      `                                                                                                                                                                                                           `````   