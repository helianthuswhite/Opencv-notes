// An example program in which the
// user can draw boxes on the screen.
//
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
#include <opencv/cv.h>
#include <opencv2/highgui.hpp>
 
// Define our callback which we will install for
// mouse events.
//定义回调函数
void my_mouse_callback(
   int event, int x, int y, int flags, void* param 
);

//定义矩形和绘制变量
CvRect box;
bool drawing_box = false;
 
// A litte subroutine to draw a box onto an image
//绘制方形到图像的子程序
void draw_box( IplImage* img, CvRect rect ) {
//    绘制函数，参数分别为：图像，起始点，结束点，颜色
  cvRectangle (
    img, 
    cvPoint(box.x,box.y),
    cvPoint(box.x+box.width,box.y+box.height),
    cvScalar(0xff,0x00,0x00)    /* red */
  );
}

//通过鼠标在窗口绘制方形
int main( int argc, char* argv[] ) {
//  初始化矩形
  box = cvRect(-1,-1,0,0);
//创建图像，图像大小，数据结构，通道数
  IplImage* image = cvCreateImage(
    cvSize(200,200),
    IPL_DEPTH_8U,
    3
  );
//    将图像所有像素值初始化为0
  cvZero( image );
//    克隆图像
  IplImage* temp = cvCloneImage( image );
//  新建窗口
  cvNamedWindow( "Box Example" );
 
  // Here is the crucial moment that we actually install
  // the callback.  Note that we set the value ‘param’ to
  // be the image we are working with so that the callback
  // will have the image to edit.
  //将回调函数注册给opencv，第一个参数为窗口，第二个为回调函数，第三个为参数
  cvSetMouseCallback( 
    "Box Example", 
    my_mouse_callback, 
    (void*) image 
  );
 
  // The main program loop.  Here we copy the working image
  // to the ‘temp’ image, and if the user is drawing, then
  // put the currently contemplated box onto that temp image.
  // display the temp image, and wait 15ms for a keystroke,
  // then repeat…
  //主程序循环。我们在这里把工作图像复制到temp中，如果用户正在绘制，就把绘制好的方形显示到temp图像中
  while( 1 ) {
//      复制图像，注意跟cvCloneImage的区别，clone是全部的图像。copy主要是ROI区域
    cvCopyImage( image, temp );
    if( drawing_box ) draw_box( temp, box ); 
    cvShowImage( "Box Example", temp );
 
    if( cvWaitKey( 15 )==27 ) break;
  }
 
  // Be tidy
  //释放内存
  cvReleaseImage( &image );
  cvReleaseImage( &temp );
  cvDestroyWindow( "Box Example" );
}
 
// This is our mouse callback.  If the user
// presses the left button, we start a box.
// when the user releases that button, then we
// add the box to the current image.  When the
// mouse is dragged (with the button down) we 
// resize the box.
//这是鼠标回调函数。如果用户点击了鼠标左键，我们开始创建一个方形，当松开左键时，我们将方形添加到当前的图像上，
//并且我们可以通过拖拽来改变方形的大小
void my_mouse_callback(
   int event, int x, int y, int flags, void* param )
{
// 获取到图像参数
  IplImage* image = (IplImage*) param;
//判断事件
  switch( event ) {
//          鼠标拖动时改变方形大小
    case CV_EVENT_MOUSEMOVE: {
      if( drawing_box ) {
        box.width  = x-box.x;
        box.height = y-box.y;
      }
    }
    break;
//          鼠标左键按下
    case CV_EVENT_LBUTTONDOWN: {
      drawing_box = true;
      box = cvRect( x, y, 0, 0 );
    }
    break;
//          鼠标左键松开
    case CV_EVENT_LBUTTONUP: {
      drawing_box = false; 
      if( box.width<0  ) { 
        box.x+=box.width;  
        box.width *=-1; 
      }
      if( box.height<0 ) { 
        box.y+=box.height; 
        box.height*=-1; 
      }
//        绘制
      draw_box( image, box );
    }
    break;   
  }
}
