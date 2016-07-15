//
// Example 8-3. Finding and drawing contours on an input image
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

//Some defines we left out of the book
//书上没有的一些定义
#define CVX_RED		CV_RGB(0xff,0x00,0x00)
#define CVX_GREEN	CV_RGB(0x00,0xff,0x00)
#define CVX_BLUE	CV_RGB(0x00,0x00,0xff)

//  Example 8-3. Finding and drawing contours on an input image
//在输入图像上寻找并绘制轮廓
int main(int argc, char* argv[]) {
//    创建窗体
  cvNamedWindow( IMG1, 1 );
  IplImage* img_8uc1 = NULL;
  
  //Changed this a little for safer image loading and help if not
//    ==加载灰度图像，一小点改变让加载图像更加安全
  if(!(img_8uc1 = cvLoadImage( IMG1, CV_LOAD_IMAGE_GRAYSCALE )) ){
  printf("\nExample 8_3 Drawing Contours\nCall is:\n./ch8_ex8_3 image\n\n");
  return -1;}
  
//  创建轮廓图像
  IplImage* img_edge = cvCreateImage( cvGetSize(img_8uc1), 8, 1 );
  IplImage* img_8uc3 = cvCreateImage( cvGetSize(img_8uc1), 8, 3 );
//    二值化处理，参数：原图像、目的图、阈值、最后一个参数的最大值、最后一个参数
  cvThreshold( img_8uc1, img_edge, 128, 255, CV_THRESH_BINARY );
//    创建序列存储器
  CvMemStorage* storage = cvCreateMemStorage();
  CvSeq* first_contour = NULL;
//    查找轮廓，返回检测到轮廓的数量
  int Nc = cvFindContours(
     img_edge,
     storage,
     &first_contour,
     sizeof(CvContour),
     CV_RETR_LIST // Try all four values and see what happens  尝试一下不同的四个参数，看看会发生什么
  );
  int n=0,k;
  printf("\n\nHit any key to draw the next contour, ESC to quit\n\n");
  printf( "Total Contours Detected: %d\n", Nc );
//    绘制出所有轮廓，轮廓通过h_next连接
  for( CvSeq* c=first_contour; c!=NULL; c=c->h_next ) {
     cvCvtColor( img_8uc1, img_8uc3, CV_GRAY2BGR );
     cvDrawContours(
        img_8uc3,
        c,
        CVX_RED,  //Yarg, these are defined above, but not in the book.  Oops
        CVX_BLUE,
        0,        // Try different values of max_level, and see what happens
        2,
        8
     );
     printf("Contour #%d\n", n );
//      显示结果
     cvShowImage( IMG1, img_8uc3 );
//      输出所有的元素个数
     printf(" %d elements:\n", c->total );
//      输出每个元素的位置
     for( int i=0; i<c->total; ++i ) {
     CvPoint* p = CV_GET_SEQ_ELEM( CvPoint, c, i );
        printf("    (%d,%d)\n", p->x, p->y );
     }
//      ESC退出
     if((k = cvWaitKey()&0x7F) == 27)
       break;
     n++;
  }
//    结束所有的轮廓绘制
  printf("Finished all contours. Hit key to finish\n");
  cvCvtColor( img_8uc1, img_8uc3, CV_GRAY2BGR );
//    显示一波最后的结果
  cvShowImage( IMG1, img_8uc3 );
  cvWaitKey(0);
  cvDestroyWindow( IMG1 );
  cvReleaseImage( &img_8uc1 );
  cvReleaseImage( &img_8uc3 );
  cvReleaseImage( &img_edge );
  return 0;
}

