#include "capture.h"

//摄像头内参
//Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
float cm[3][3] = {{19511.65368981929, 0, 450.4902595035327}, 
{ 0, 17716.34851590898, 650.0349068087045}, 
{0, 0, 1}};
//Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
float dc[1][5] = {-64.80776352480207, -804.2657326581508, -1.020264299239374, 0.6373351195983814, -3.074189917192802};
// float dc[1][5] = {0 ,0, 0, 0, 0};

//单应性矩阵
float H[3][3] = {{-2.848447835427322, 0.0484155439449403, 2639.131300438697}, 
{0.1475151077744222, -2.894159109663521, 2410.521841109304}, 
{2.387804733324391e-06, 1.276341655682765e-05, 1}};

//初始化摄像头参数
void capinit(VideoCapture& capture)
{
    capture.set(CAP_PROP_FOURCC,VideoWriter::fourcc('M','J','P','G'));
    capture.set(CAP_PROP_AUTO_WB,0);
	capture.set(CAP_PROP_WB_TEMPERATURE,5000);
    //capture.set(CAP_PROP_AUTO_EXPOSURE,1);
	capture.set(CAP_PROP_FRAME_WIDTH ,Frame_WIDTH);
	capture.set(CAP_PROP_FRAME_HEIGHT ,Frame_HEIGHT);
	printf("CAP_WIDTH = %f\r\n" , capture.get(CAP_PROP_FRAME_WIDTH));
    printf("CAP_HEIGHT = %f\r\n" , capture.get(CAP_PROP_FRAME_HEIGHT));
    printf("帧率 = %f\r\n" , capture.get(CAP_PROP_FPS));
    printf("亮度 = %f\r\n" , capture.get(CAP_PROP_BRIGHTNESS));
    printf("对比度 = %f\r\n" , capture.get(CAP_PROP_CONTRAST));
    printf("饱和度 = %f\r\n" , capture.get(CAP_PROP_SATURATION));
    printf("色相 = %f\r\n" , capture.get(CAP_PROP_HUE));
    printf("增益 = %f\r\n" , capture.get(CAP_PROP_GAIN));
    //capture.set(CAP_PROP_EXPOSURE ,113);
    printf("曝光 = %f\r\n" , capture.get(CAP_PROP_EXPOSURE));
}
//拍照
void shoot(VideoCapture &capture)
{
	//摄像机内参
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, cm);
	Mat distCoeffs = Mat(1, 5, CV_32FC1, dc);
	

    Mat frame;
	Mat frame_undistort;
    int cnt=0;
	char imgname[50];
    while (true)
	{
		capture >> frame; 
		undistort(frame,frame_undistort,cameraMatrix,distCoeffs);
		imshow("frame", frame);
		imshow("frame_undistort", frame_undistort);


		char key = waitKey(1);
		if(key=='s')
		{
			cnt++;
			sprintf(imgname,"../shootimages/img_%d.jpg",cnt);
			imwrite(imgname,frame_undistort);
		}
			
		else if( key == 'q' )
 			break;
	}
}
//标定
void capcalibrate(VideoCapture &capture)
{
    int CHECKERBOARD[2]{6,9}; 
    // Creating vector to store vectors of 3D points for each checkerboard image
	std::vector<std::vector<cv::Point3f> > objpoints;
	
	// Creating vector to store vectors of 2D points for each checkerboard image
	std::vector<std::vector<cv::Point2f> > imgpoints;
	
	// Defining the world coordinates for 3D points
	std::vector<cv::Point3f> objp;
	for(int i{0}; i<CHECKERBOARD[1]; i++)
	{
		for(int j{0}; j<CHECKERBOARD[0]; j++)
		objp.push_back(cv::Point3f(j,i,0));
	}
	
	
	// Extracting path of individual image stored in a given directory
	std::vector<cv::String> images;
	// Path of the folder containing checkerboard images
	std::string path = "../shootimages/*.jpg";
	
	cv::glob(path, images);
	
	cv::Mat frame, gray;
	// vector to store the pixel coordinates of detected checker board corners 
	std::vector<cv::Point2f> corner_pts;
	bool success;
	
	// Looping over all the images in the directory
	for(int i{0}; i<images.size(); i++)
	{
		frame = cv::imread(images[i]);
		cv::cvtColor(frame,gray,cv::COLOR_BGR2GRAY);
	
		// Finding checker board corners
		// If desired number of corners are found in the image then success = true  
		success = cv::findChessboardCorners(gray, cv::Size(CHECKERBOARD[0], CHECKERBOARD[1]), 
		corner_pts, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);
		
		/* 
		* If desired number of corner are detected,
		* we refine the pixel coordinates and display 
		* them on the images of checker board
		*/
		if(success)
		{
		cv::TermCriteria criteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.001);
		
		// refining pixel coordinates for given 2d points.
		cv::cornerSubPix(gray,corner_pts,cv::Size(11,11), cv::Size(-1,-1),criteria);
		
		// Displaying the detected corner points on the checker board
		cv::drawChessboardCorners(frame, cv::Size(CHECKERBOARD[0], CHECKERBOARD[1]), corner_pts, success);
		
		objpoints.push_back(objp);
		imgpoints.push_back(corner_pts);
		}
	
		cv::imshow("Image",frame);
		cv::waitKey(0);
	}
	
	cv::destroyAllWindows();
	
	cv::Mat cameraMatrix,distCoeffs,R,T;
	
	/*
	* Performing camera calibration by 
	* passing the value of known 3D points (objpoints)
	* and corresponding pixel coordinates of the 
	* detected corners (imgpoints)
	*/
	cv::calibrateCamera(objpoints, imgpoints, cv::Size(gray.rows,gray.cols), cameraMatrix, distCoeffs, R, T);
	
	std::cout << "cameraMatrix : " << cameraMatrix << std::endl;
	std::cout << "distCoeffs : " << distCoeffs << std::endl;
	std::cout << "Rotation vector : " << R << std::endl;
	std::cout << "Translation vector : " << T << std::endl;
}

//滑动条调整
void trackbarinrange(VideoCapture &capture)
{
	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 100;
	int iHighH = 140;

	int iLowS = 90;
	int iHighS = 255;

	int iLowV = 90;
	int iHighV = 255;
	
	cvCreateTrackbar("iLowH", "Control", &iLowH, 255); //B (0 - 255)
	cvCreateTrackbar("iHighH", "Control", &iHighH, 255);

	cvCreateTrackbar("iLowS", "Control", &iLowS, 255); //G (0 - 255)
	cvCreateTrackbar("iHighS", "Control", &iHighS, 255);

	cvCreateTrackbar("iLowV", "Control", &iLowV, 255); //R (0 - 255)
	cvCreateTrackbar("iHighV", "Control", &iHighV, 255);

	while (true)
	{
		Mat imgOriginal;
		capture >> imgOriginal;
		Mat imgHSV;
		vector<Mat> bgrSplit;
		//imgOriginal = imread("../img_map.jpg");
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		split(imgHSV, bgrSplit);
		//equalizeHist(bgrSplit[0], bgrSplit[0]);
		imshow("0", bgrSplit[0]);
		imshow("1", bgrSplit[1]);
		imshow("2", bgrSplit[2]);
		//merge(bgrSplit, imgHSV);
		Mat imgThresholded;
	
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		imshow("Original", imgOriginal); //show the original image
		waitKey(1);
	}
}
