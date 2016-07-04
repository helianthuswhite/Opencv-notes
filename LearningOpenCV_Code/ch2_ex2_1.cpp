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

int main( int argc, char** argv )
{
//    将图片加载至内存，并且根据图片的格式自动为图片的数据结构分配内存
  IplImage* img = cvLoadImage( IMG1 );
//    highgui库中的函数，创建一个窗口，参数设置为窗口大小根据图片自动调整
  cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE );
//    将图片显示在窗口，第一个参数为显示的窗口，第二个为图片地址
  cvShowImage("Example1", img );
//    使程序暂停，等待用户触发一个按键操作；正参数为等待ms输数，0或者负参数为一直等待
  cvWaitKey(0);
//    释放为图片分配的内存
  cvReleaseImage( &img );
//    销毁显示图像文件的窗口
  cvDestroyWindow("Example1");
}
