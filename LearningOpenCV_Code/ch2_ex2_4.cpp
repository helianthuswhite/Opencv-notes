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

void example2_4( IplImage* image )
{
    // Create some windows to show the input
    // and output images in.
    //
//    分别创建输入和输出窗口
    cvNamedWindow( "Example2_4-in", CV_WINDOW_AUTOSIZE );
    cvNamedWindow( "Example2_4-out", CV_WINDOW_AUTOSIZE );
    
    // Create a window to show our input image
//    显示图片
    cvShowImage( "Example2_4-in", image );
    
    // Create an image to hold the smoothed output
//    第一个参数是图像结构大小，第二个每个像素的数据类型，第三个参数是图像通道数
    IplImage* out = cvCreateImage(
        cvGetSize(image),
        IPL_DEPTH_8U,
        3
    );
    
    // Do the smoothing
//    对图片进行平滑处理
    cvSmooth( image, out, CV_GAUSSIAN, 5,5 );
    cvSmooth( out, out, CV_GAUSSIAN, 5, 5);
    
    // Show the smoothed image in the output window
//    显示处理后的图像
    cvShowImage( "Example2_4-out", out );
    
    // Be tidy
//    释放内存
    cvReleaseImage( &out );

    // Wait for the user to hit a key, then clean up the windows
//    等待程序结束以及销毁窗口
    cvWaitKey( 0 );
    cvDestroyWindow("Example2_4-in" );
    cvDestroyWindow("Example2_4-out" );
    
}

int main( int argc, char** argv )
{
//    加载图像
  IplImage* img = cvLoadImage( IMG1 );
//    创建窗口
  cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE );
//    显示图像
  cvShowImage("Example1", img );
//    处理图像
  example2_4( img );
//  cvWaitKey(0);
  cvReleaseImage( &img );
  cvDestroyWindow("Example1");
}

