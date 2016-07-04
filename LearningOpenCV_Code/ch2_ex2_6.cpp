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
//边缘检测输出单通道（灰度级）图像
IplImage* doCanny(
    IplImage* in,
    double    lowThresh,
    double    highThresh,
    double    aperture)
{
//    如果不是灰度也就是单通道图像直接返回，因为canny只能处理单通道图像
    if (in->nChannels != 1)
        return(0); // Canny only handles gray scale images
//    创建输出图像
    IplImage* out = cvCreateImage(
        cvGetSize( in ),
        in->depth, //IPL_DEPTH_8U,    
        1);
//    进行边缘检测
    cvCanny( in, out, lowThresh, highThresh, aperture );
    return( out );
};

int main( int argc, char** argv )
{
//    加载图像
  IplImage* img_rgb = cvLoadImage( IMG1 );
//    将图像变成单通道
  IplImage* img_gry = cvCreateImage( cvSize( img_rgb->width,img_rgb->height ), img_rgb->depth, 1);
//    RGB颜色的转换，这里转换成灰度图像Gray
  cvCvtColor(img_rgb, img_gry ,CV_BGR2GRAY);
//    创建窗口
  cvNamedWindow("Example Gray", CV_WINDOW_AUTOSIZE );
  cvNamedWindow("Example Canny", CV_WINDOW_AUTOSIZE );
//    显示处理前图像
  cvShowImage("Example Gray", img_gry );
//    开始处理
  IplImage* img_cny = doCanny( img_gry, 10, 100, 3 );
//    显示处理后图像
  cvShowImage("Example Canny", img_cny );
  cvWaitKey(0);
//    后续的处理，窗口、内存
  cvReleaseImage( &img_rgb);
  cvReleaseImage( &img_gry);
  cvReleaseImage( &img_cny);
  cvDestroyWindow("Example Gray");
  cvDestroyWindow("Example Canny");
}
