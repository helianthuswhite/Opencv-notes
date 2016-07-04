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
#include "opemcv2/highgui.hpp"

int main( int argc, char** argv ) {
//    创建窗体
    cvNamedWindow( "Example2_9", CV_WINDOW_AUTOSIZE );
    CvCapture* capture;
    if (argc==1) {
//        从摄像头获取图像
        capture = cvCreateCameraCapture( 0 );
    } else {
//        从视频文件获取图像
        capture = cvCreateFileCapture( VIDEO1 );
    }
    assert( capture != NULL );

    IplImage* frame;
    while(1) {
//        显示获取的图像
        frame = cvQueryFrame( capture );
        if( !frame ) break;
        cvShowImage( "Example2_9", frame );
//        等待10ms一次循环
        char c = cvWaitKey(10);
//        当按下ESC键退出
        if( c == 27 ) break;
    }
//    释放内存并销毁窗体
    cvReleaseCapture( &capture );
    cvDestroyWindow( "Example2_9" );
}
