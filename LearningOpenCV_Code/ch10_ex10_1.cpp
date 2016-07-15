// Example 10-1. Pyramid Lucas-Kanade optical flow code
//
/* *************** License:**************************
   Oct. 3, 2008
   Right to use this code in any way you want without warrenty, support or any guarentee of it working.

   BOOK: It would be nice if you cited it:
   Learning OpenCV: Computer Vision with the OpenCV Library
     by Gary Bradski and Adrian Kaehler
     Published by O'Reilly Media, October 3, 2008
 
   AVAILABLE AT: 
     http://www.amazon.com/Learning-OpenCV-Computer-Vision-Library/dp/0596516134
     Or: http://oreilly.com/catalog/9780596516130/
     ISBN-10: 0596516134 or: ISBN-13: 978-0596516130    

   OTHER OPENCV SITES:
   * The source code is on sourceforge at:
     http://sourceforge.net/projects/opencvlibrary/
   * The OpenCV wiki page (As of Oct 1, 2008 this is down for changing over servers, but should come back):
     http://opencvlibrary.sourceforge.net/
   * An active user group is at:
     http://tech.groups.yahoo.com/group/OpenCV/
   * The minutes of weekly OpenCV development meetings are at:
     http://pr.willowgarage.com/wiki/OpenCV
 
 
 ADD ALL NOTES BY W_LITTLEWHITE
 * The github is at:
 https://github.com/964873559

 
   ************************************************** */

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv2/highgui.hpp>
#include <stdio.h>

//金字塔Lucas-Kanade光流代码
const int MAX_CORNERS = 500;
int main(int argc, char** argv) {
   // Initialize, load two images from the file system, and
   // allocate the images and other structures we will need for
   // results.
	//初始化，加载两张图像，分配我们所需要的内存
	IplImage* imgA = cvLoadImage("/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/LearningOpenCV_Code/OpticalFlow0.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* imgB = cvLoadImage("/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/LearningOpenCV_Code/OpticalFlow1.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	CvSize      img_sz    = cvGetSize( imgA );
	int         win_size = 10;
	IplImage* imgC = cvLoadImage("/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/LearningOpenCV_Code/OpticalFlow1.jpg",CV_LOAD_IMAGE_UNCHANGED);
	
	// The first thing we need to do is get the features
	// we want to track.
	//我们首先要做的是获取到角点
	IplImage* eig_image = cvCreateImage( img_sz, IPL_DEPTH_32F, 1 );
	IplImage* tmp_image = cvCreateImage( img_sz, IPL_DEPTH_32F, 1 );
	int              corner_count = MAX_CORNERS;
	CvPoint2D32f* cornersA        = new CvPoint2D32f[ MAX_CORNERS ];
//    获取角点函数，参数为：8位或32位单通道图图像，2、3参数是大小与输入相同的32位单通道图像，函数输出32位角点数组，检测到的角点数目，角点可接受的最小特征值，角点之间的最小距离，指定输入图像中参与角点计算的像素点，计算导数自相关矩阵时指定点的领域，设定角点的定义，设置Hession自相关矩阵对Hessian行列式相对权重的权重系数
	cvGoodFeaturesToTrack(
		imgA,
		eig_image,
		tmp_image,
		cornersA,
		&corner_count,
		0.01,
		5.0,
		0,
		3,
		0,
		0.04
	);
//    寻找亚像素精度的角点位置，参数为：输入8位单通道灰度图像，角点的初始位置，角点的数目，等式产生窗口的位置，输入禁区，迭代终止条件
	cvFindCornerSubPix(
		imgA,
		cornersA,
		corner_count,
		cvSize(win_size,win_size),
		cvSize(-1,-1),
		cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03)
	);
	// Call the Lucas Kanade algorithm
	//执行LK光流算法
	char features_found[ MAX_CORNERS ];
	float feature_errors[ MAX_CORNERS ];
	CvSize pyr_sz = cvSize( imgA->width+8, imgB->height/3 );
	IplImage* pyrA = cvCreateImage( pyr_sz, IPL_DEPTH_32F, 1 );
  IplImage* pyrB = cvCreateImage( pyr_sz, IPL_DEPTH_32F, 1 );
  CvPoint2D32f* cornersB        = new CvPoint2D32f[ MAX_CORNERS ];
//    参数为：初始图像，最终图像，3、4为申请存放图像的金字塔缓存，用于寻找位置的点，存放新的位置点，寻找位置点的数目，创建运动窗口的尺寸，金字塔的栈层数，在第二幅图像中是否发现相应点的状态，被跟踪点的原始图像小区域与此点在第二幅图像小区域间的差的数组，可以删除那些局部外观小区域随点运动变化剧烈的点，终止条件，细微控制
  cvCalcOpticalFlowPyrLK(
     imgA,
     imgB,
     pyrA,
     pyrB,
     cornersA,
     cornersB,
     corner_count,
     cvSize( win_size,win_size ),
     5,
     features_found,
     feature_errors,
     cvTermCriteria( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, .3 ),
     0
  );
  // Now make some image of what we are looking at:
  //产生一些我们顶着的图像，绘制出运动变化的点
  for( int i=0; i<corner_count; i++ ) {
     if( features_found[i]==0|| feature_errors[i]>550 ) {
 //       printf("Error is %f/n",feature_errors[i]);
        continue;
     }
 //    printf("Got it/n");
     CvPoint p0 = cvPoint(
        cvRound( cornersA[i].x ),
        cvRound( cornersA[i].y )
     );
     CvPoint p1 = cvPoint(
        cvRound( cornersB[i].x ),
        cvRound( cornersB[i].y )
     );
     cvLine( imgC, p0, p1, CV_RGB(255,0,0),2 );
  }
//    显示一波结果
  cvNamedWindow("ImageA",0);
  cvNamedWindow("ImageB",0);
  cvNamedWindow("LKpyr_OpticalFlow",0);
  cvShowImage("ImageA",imgA);
  cvShowImage("ImageB",imgB);
  cvShowImage("LKpyr_OpticalFlow",imgC);
  cvWaitKey(0);
  return 0;
}

