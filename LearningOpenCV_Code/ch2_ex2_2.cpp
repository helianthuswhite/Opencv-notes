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
#include <opencv2/highgui.hpp>

int main( int argc, char** argv ) {
    //创建窗口
    cvNamedWindow( "Example2", CV_WINDOW_AUTOSIZE );
//    获取要读入的avi文件
    //CvCapture* capture = cvCaptureFromAVI( argv[1] ); // either one will work
    CvCapture* capture = cvCreateFileCapture( VIDEO1);
//    创建图片指针
    IplImage* frame;
    while(1) {
//        将下一帧视频载入内存
        frame = cvQueryFrame( capture );
        if( !frame ) break;
//        以单帧方式显示视频
        cvShowImage( "Example2", frame );
//        每隔33ms等待一次，如果触发按键，则返回按键的ASCII码
        char c = cvWaitKey(33);
//        当触发ESC键时退出循环
        if( c == 27 ) break;
    }
//    释放CvCapture结构开辟的空间
    cvReleaseCapture( &capture );
//    销毁窗口
    cvDestroyWindow( "Example2" );
}
