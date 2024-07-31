#include "rectget.h"
#include "capture.h"
//提取方格位置
int blocklocationget(Mat& frame_undistort,Rect dstrect[9])
{
    vector<Rect> result;
    result.clear();
    //int resultcnt = -1;
    Mat frame;
    //frame = imread("../img_map.jpg");
    //frame = frame_undistort(Rect(100,0,1080,720));
    frame = frame_undistort;
    //imshow("frame", frame);
    Mat frame_blur;
    Mat frame_gray;
    Mat gray_canny;
    Mat frame_inRange;
    Mat frame_HSV;
    //高斯模糊
    GaussianBlur(frame,frame_blur,Size(5,5),1);
    //inrange
    cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
	inRange(frame_HSV, Scalar(0, 0, 87), Scalar(255, 255, 255), frame_inRange);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    erode(frame_inRange,frame_inRange,kernel,Point(-1,-1),2);
    dilate(frame_inRange,frame_inRange,kernel,Point(-1,-1),2);
   
	
	//imshow("frame_inRange", frame_inRange);
    waitKey(1);
    //轮廓提取求roi
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(frame_inRange,contours,hierarchy,RETR_CCOMP,
    CHAIN_APPROX_NONE);
    Mat framedraw = frame.clone();
    if(contours.size()>0)
    {
        int cnt = 0;
        for(int i=0;i<contours.size();i++)
        {
            //先计算最小外接矩形的面积：
            RotatedRect minrect = minAreaRect(contours[i]);    //最小外接矩形
            int area = contourArea(contours[i]);//计算轮廓面积
            float hpw = minrect.size.height / minrect.size.width;
            //cout << area << endl;
            if(area>9000&&area<20000&&hpw<1.2&&hpw>0.2)
            {
                //cout << "area :" << area << endl;
                //获取最小外接矩形
                cv::Rect roi = cv::boundingRect(cv::Mat(contours[i]));
                Point roitl = roi.tl();
                Point roibr = roi.br();
                int offsetx = (roibr.x-roitl.x)*0.2;
                int offsety = (roibr.y-roitl.y)*0.2;
                roi = Rect(Point(roitl.x+offsetx,roitl.y+offsety),Point(roibr.x-offsetx,roibr.y-offsety));
                rectangle(framedraw,roi,Scalar(0,0,255),2,8);
                result.push_back(roi);

                // Point2f rect_point[4];
                // minrect.points(rect_point);
                // line(framedraw,rect_point[0],rect_point[1],Scalar(255,255,0),2);
                // line(framedraw,rect_point[1],rect_point[2],Scalar(255,255,0),2);
                // line(framedraw,rect_point[2],rect_point[3],Scalar(255,255,0),2);
                // line(framedraw,rect_point[3],rect_point[0],Scalar(255,255,0),2);
                // rectangle(framedraw,roi,Scalar(0,0,255),2,8);
                //result.push_back(roi);
            }
        }
    }
    if(result.size()==9)
    {
        ordermyrect(framedraw,result,dstrect);
        //imshow("framedraw",framedraw);
        return 1;
    }
    else
    {
        return 0;
    }
}
//排序方格
void ordermyrect(Mat& framedraw,vector<Rect>& input,Rect dstrect[9])
{
    //先找minx,miny.maxx,maxy
    int minx,miny,maxx,maxy;
    minx = 2000;
    miny = 2000;
    maxx = 0;
    maxy = 0;
    int minx_i,miny_i,maxx_i,maxy_i;
    for(int i=0;i<input.size();i++)
    {
        int curx = input[i].tl().x;
        int cury = input[i].tl().y;
        if(curx<minx)
        {
            minx=curx;
            minx_i = i;
        }
        if(curx>maxx)
        {
            maxx=curx;
            maxx_i = i;
        }
        if(cury<miny)
        {
            miny=cury;
            miny_i = i;
        }
        if(cury>maxy)
        {
            maxy=cury;
            maxy_i = i;
        }
    }
    //如果它们各不相同,说明角度大于45度,则采用特殊方法排列
    if(minx_i!=miny_i&&minx_i!=maxy_i&&minx_i!=maxx_i&&
    miny_i!=maxy_i&&miny_i!=maxx_i
    &&maxy_i!=maxx_i)
    // if(0)
    {
        // cout << minx_i << maxx_i << miny_i << maxy_i << endl;
        dstrect[0]=input[minx_i];
        dstrect[2]=input[miny_i];
        dstrect[6]=input[maxy_i];
        dstrect[8]=input[maxx_i];
        if(dstrect[2].tl().x>dstrect[6].tl().x)
        {
            Rect tmp;
            tmp = dstrect[2];
            dstrect[2] = dstrect[6];
            dstrect[6] = tmp;
        }
        if(dstrect[2].tl().y<dstrect[0].tl().y)
        {
            Rect tmp;
            tmp = dstrect[2];
            dstrect[2] = dstrect[0];
            dstrect[0] = tmp;
        }
        if(dstrect[8].tl().y<dstrect[6].tl().y)
        {
            Rect tmp;
            tmp = dstrect[6];
            dstrect[6] = dstrect[8];
            dstrect[8] = tmp;
        }
        // putText(framedraw, "1",dstrect[0].tl(),FONT_HERSHEY_PLAIN,
        // 3,Scalar(0,100,255),3);
        // putText(framedraw, "3",dstrect[2].tl(),FONT_HERSHEY_PLAIN,
        // 3,Scalar(0,100,255),3);
        // putText(framedraw, "7",dstrect[6].tl(),FONT_HERSHEY_PLAIN,
        // 3,Scalar(0,100,255),3);
        // putText(framedraw, "9",dstrect[8].tl(),FONT_HERSHEY_PLAIN,
        // 3,Scalar(0,100,255),3);
        // //最后对中间五个点排列
        vector<Rect> rects_tmp;
        for(int i=0;i<input.size();i++)
        {
            if(i!=minx_i&&i!=maxx_i&&i!=miny_i&&i!=maxy_i)
            {
                rects_tmp.push_back(input[i]);
            }
        }
        //cout << rects_tmp.size() << endl;
        for(int i=0;i<rects_tmp.size()-1;i++) 
        {
            for(int j=0;j<rects_tmp.size()-1-i;j++) 
            {
                if (rects_tmp[j].tl().x>rects_tmp[j+1].tl().x) 
                {
                    //如果左边的数大于右边的数，则交换，保证右边的数字最大
                    Rect tem = rects_tmp[j];
                    rects_tmp[j] = rects_tmp[j+1];
                    rects_tmp[j+1] = tem;
                }
            }
        }
        //对中间三个点再冒泡
        for(int i=0;i<3-1;i++) 
        {
            for(int j=0;j<3-1-i;j++) 
            {
                if (rects_tmp[j+1].tl().y>rects_tmp[j+1+1].tl().y) 
                {
                    //如果左边的数大于右边的数，则交换，保证右边的数字最大
                    Rect tem = rects_tmp[j+1];
                    rects_tmp[j+1] = rects_tmp[j+1+1];
                    rects_tmp[j+1+1] = tem;
                }
            }
        }
        // putText(framedraw, "2",rects_tmp[0].tl(),FONT_HERSHEY_PLAIN,
        // 3,Scalar(0,100,255),3);
        // putText(framedraw, "4",rects_tmp[1].tl(),FONT_HERSHEY_PLAIN,
        // 3,Scalar(0,100,255),3);
        // putText(framedraw, "5",rects_tmp[2].tl(),FONT_HERSHEY_PLAIN,
        // 3,Scalar(0,100,255),3);
        // putText(framedraw, "6",rects_tmp[3].tl(),FONT_HERSHEY_PLAIN,
        // 3,Scalar(0,100,255),3);
        // putText(framedraw, "8",rects_tmp[4].tl(),FONT_HERSHEY_PLAIN,
        // 3,Scalar(0,100,255),3);
        dstrect[1] = rects_tmp[0];
        dstrect[3] = rects_tmp[1];
        dstrect[4] = rects_tmp[2];
        dstrect[5] = rects_tmp[3];
        dstrect[7] = rects_tmp[4];
        rects_tmp.clear();
    }
    else//否则两个冒泡排序解决
    {
        for(int i=0;i<input.size()-1;i++) 
        {
            for(int j=0;j<input.size()-1-i;j++) 
            {
                if (input[j].tl().x>input[j+1].tl().x) 
                {
                    //如果左边的数大于右边的数，则交换，保证右边的数字最大
                    Rect tem = input[j];
                    input[j] = input[j+1];
                    input[j+1] = tem;
                }
            }
        }
        for(int k=0;k<3;k++)
        {
            for(int i=0;i<3-1;i++) 
            {
                for(int j=0;j<3-1-i;j++) 
                {
                    if (input[k*3+j].tl().y>input[k*3+j+1].tl().y) 
                    {
                        //如果左边的数大于右边的数，则交换，保证右边的数字最大
                        Rect tem = input[k*3+j];
                        input[k*3+j] = input[k*3+j+1];
                        input[k*3+j+1] = tem;
                    }
                }
            }
        }
        for(int k=0;k<9;k++)
        {
            dstrect[k] = input[k];
        }
    }
    
    putText(framedraw, "1",dstrect[0].tl(),FONT_HERSHEY_PLAIN,
	3,Scalar(0,100,255),3);
    putText(framedraw, "2",dstrect[1].tl(),FONT_HERSHEY_PLAIN,
	3,Scalar(0,100,255),3);
    putText(framedraw, "3",dstrect[2].tl(),FONT_HERSHEY_PLAIN,
	3,Scalar(0,100,255),3);
    putText(framedraw, "4",dstrect[3].tl(),FONT_HERSHEY_PLAIN,
	3,Scalar(0,100,255),3);
    putText(framedraw, "5",dstrect[4].tl(),FONT_HERSHEY_PLAIN,
	3,Scalar(0,100,255),3);    
    putText(framedraw, "6",dstrect[5].tl(),FONT_HERSHEY_PLAIN,
	3,Scalar(0,100,255),3);
    putText(framedraw, "7",dstrect[6].tl(),FONT_HERSHEY_PLAIN,
	3,Scalar(0,100,255),3);
    putText(framedraw, "8",dstrect[7].tl(),FONT_HERSHEY_PLAIN,
	3,Scalar(0,100,255),3);
    putText(framedraw, "9",dstrect[8].tl(),FONT_HERSHEY_PLAIN,
	3,Scalar(0,100,255),3);
    
    input.clear();
}
//提取方格中为什么棋子
void chessget(Mat& frame,Rect dstrect[9],int chessmap [9])
{
    for(int i=0;i<9;i++)
    {
        Mat frame_roi = frame(dstrect[i]);
        resize(frame_roi,frame_roi,Size(50,50));
        Mat frame_HSV;
        Mat frame_gray;
        Mat frame_inRange;
        cvtColor(frame_roi, frame_HSV, COLOR_BGR2HSV);
        cvtColor(frame_roi, frame_gray, COLOR_BGR2GRAY);
        //黑色阈值
        inRange(frame_HSV, Scalar(0, 0, 87), Scalar(255, 255, 255), frame_inRange);
        //threshold(frame_gray, frame_inRange, 125, 255, THRESH_OTSU);
        //imshow("frame_inRange",frame_inRange);
        //waitKey(1000);
        int blackblock = 0;
        for(int i = 0;i<frame_inRange.rows;i++)
        {
            for(int j = 0;j<frame_inRange.cols;j++)
            {
                if(frame_inRange.at<uchar>(Point(j,i))==0)
                {
                    blackblock++;
                }
            }
        }
        //白色阈值
        inRange(frame_HSV, Scalar(0, 60, 0), Scalar(255, 255, 234), frame_inRange);
        //threshold(frame_gray, frame_inRange, 125, 255, THRESH_OTSU);
        //imshow("frame_inRange",frame_inRange);
        //waitKey(1000);
        int whiteblock = 0;
        for(int i = 0;i<frame_inRange.rows;i++)
        {
            for(int j = 0;j<frame_inRange.cols;j++)
            {
                if(frame_inRange.at<uchar>(Point(j,i))==0)
                {
                    whiteblock++;
                }
            }
        }
        if(blackblock>=900)
        {
            chessmap[i]=1;//黑色是1
        }
        else if(whiteblock>=900)
        {
            chessmap[i]=2;//白色是2
        }
        else
        {
            chessmap[i]=0;//无棋子是0
        }
    }
    cout << "chessmap[i]" << endl;
    for(int i = 0;i<9;i++)
        cout << chessmap[i] << " ";
    cout << endl;
}
//获取机器坐标系对应点
void Torealcoordinate(Point2f srcp,Point2f dstp)
{
    //单应性矩阵
	Mat Hm = Mat(3, 3, CV_32FC1, H);
    Mat src_pm = Mat::zeros(3,1,CV_32FC1);
    Mat dst_pm = Mat::zeros(3,1,CV_32FC1);
    src_pm.at<float>(0,0) = srcp.x;
    src_pm.at<float>(0,1) = srcp.y;
    src_pm.at<float>(0,2) = 1;
    dst_pm = Hm*src_pm;
    cout << dst_pm << endl;
}