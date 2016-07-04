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
#include "opencv/cv.h"
#include "opencv2/highgui.hpp"

IplImage* doPyrDown(
  IplImage* in,
  int       filter = IPL_GAUSSIAN_5x5)
{

    // Best to make sure input image is divisible by two.
    //
//    assert( in->width%2 == 0 && in->height%2 == 0 );
//    创建图像，三个参数，大小，数据结构，通道
    IplImage* out = cvCreateImage(
        cvSize( in->width/2, in->height/2 ),
        in->depth,
        in->nChannels
    );
//    图像缩放处理
    cvPyrDown( in, out );
    return( out );
};

int main( int argc, char** argv )
{
//    加载图像
  IplImage* img = cvLoadImage( IMG1 );
//    创建缩小的图像
  IplImage* img2 = cvCreateImage( cvSize( img->width/2,img->height/2 ), img->depth, img->nChannels);
//    创建窗体1和2
  cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE );
  cvNamedWindow("Example2", CV_WINDOW_AUTOSIZE );
//    显示图像
  cvShowImage("Example1", img );
//    处理图像
  img2 = doPyrDown( img );
  cvShowImage("Example2", img2 );
  cvWaitKey(0);
//    释放内存，销毁窗口
  cvReleaseImage( &img );
  cvReleaseImage( &img2 );
  cvDestroyWindow("Example1");
  cvDestroyWindow("Example2");
}
