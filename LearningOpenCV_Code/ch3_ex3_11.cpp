/* License:
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

*/
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv2/highgui.hpp>

//最大化HSV图像中“S”和“V”的部分
void saturate_sv( IplImage* img ) {
  for( int y=0; y<img->height; y++ ) {
//      ptr指针指向y行起始位置
    uchar* ptr = (uchar*) (
      img->imageData + y * img->widthStep 
    );
//      从指针中析出饱和度和高度在x维的值
    for( int x=0; x<img->width; x++ ) {
      ptr[3*x+1] = 255;
      ptr[3*x+2] = 255;
    }
  }
}

int main( int argc, char** argv )
{
//    读取图像和创建窗体
  IplImage* img = cvLoadImage( IMG1 );
  cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE );
//    处理图像
  saturate_sv(img);
//    后续工作
  cvShowImage("Example1", img );
  cvWaitKey(0);
  cvReleaseImage( &img );
  cvDestroyWindow("Example1");
}


