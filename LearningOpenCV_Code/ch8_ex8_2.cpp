//
// Example 8-2. Finding contours based on a trackbar’s location; the contours are updated
//              whenever the trackbar is moved
//
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
 
   ************************************************** *///
//


#include <opencv/cv.h>
#include <opencv2/highgui.hpp>
#include <stdio.h>

IplImage*    g_image    = NULL;
IplImage*    g_gray    = NULL;
int        g_thresh  = 100;
CvMemStorage*  g_storage  = NULL;

//处理图像函数
void on_trackbar(int) {
//    若g_storage为NULL，则g_gray被初始化为单通道黑色图像，并用cvCreateMemStorage创建内存储器
  if( g_storage==NULL ) {
    g_gray = cvCreateImage( cvGetSize(g_image), 8, 1 );
    g_storage = cvCreateMemStorage(0);
  } else {
//      若g_storage不为NULL则先清除内存储器中空间
    cvClearMemStorage( g_storage );
  }
//    创建指针存储轮廓
  CvSeq* contours = 0;
//    创建灰度图像
  cvCvtColor( g_image, g_gray, CV_BGR2GRAY );
//    进行二值化处理
  cvThreshold( g_gray, g_gray, g_thresh, 255, CV_THRESH_BINARY );
//    寻找轮廓
  cvFindContours( g_gray, g_storage, &contours );
//    像素值初始化为0
  cvZero( g_gray );
//    用白色绘制出轮廓
  if( contours )
    cvDrawContours( 
      g_gray, 
      contours, 
      cvScalarAll(255),
      cvScalarAll(255), 
      100 
    );
//    显示结果
  cvShowImage( "Contours", g_gray );
}

//根据滑动条参数检验轮廓，在活动条变化时重新检测
int main( int argc, char** argv )
{
//    加载图像
  if(!(g_image = cvLoadImage(IMG1)) ){
  printf("\nExample 8_2 Contour retreival using trackbar\nCall is:\n./ch8_ex8_2 image\n");
  return -1;}
  cvNamedWindow( "Contours", 1 );
//    创建滑动条并处理图像
  cvCreateTrackbar(
    "Threshold", 
    "Contours", 
    &g_thresh, 
    255, 
    on_trackbar
  );
//    释放内存
  on_trackbar(0);
  cvWaitKey();
  return 0; 
}
