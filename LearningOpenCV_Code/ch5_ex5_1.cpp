//
//Example 5-1. Doing something with each element in the sequence of connected components returned
//             by cvPyrSegmentation(
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
 

   ************************************************** */

#include <stdio.h>
#include <opencv/cv.h>
#include <opencv2/highgui.hpp>
#include <opencv2/legacy/legacy.hpp>


//对序列中的每个元素进行操作,此序列的元素是由cvPyrSegmentation返回的连续区域
void f(
  IplImage* src, 
  IplImage* dst 
) {
//    分配存储区域，storage指针指向opencv存储区
  CvMemStorage* storage = cvCreateMemStorage(0);
//    序列的初始位置
  CvSeq* comp = NULL;
//    金字塔处理，参数分别为：输入、输出、存储、位置指针、金字塔层数、建立连接时的错误阈值，分割簇的错误阈值
//    建立连接时的错误阈值：小于等于该值得点连接；分割簇的错误阈值：小于等于该值的点看做一个区域
  cvPyrSegmentation( src, dst, storage, &comp, 4, 200, 50 );
//    获取序列元素的个数
  int n_comp = comp->total;

  for( int i=0; i<n_comp; i++ ) {
//      依次获得每一个元素的值
    CvConnectedComp* cc = (CvConnectedComp*) cvGetSeqElem( comp, i );
    // do_something_with( cc );
//      这里可以做点什么
  }
//    释放内存
  cvReleaseMemStorage( &storage );
}

int main(int argc, char** argv)
{

  // Create a named window with a the name of the file.
//    创建一个以文件命名的窗体
  cvNamedWindow( IMG1, 1 );
  // Load the image from the given file name.
//    加载图像
  IplImage* src = cvLoadImage( IMG1);
//    打开失败
  if(!src) { printf("Couldn't seem to Open %s, sorry\n",IMG1); return -1;}
//    创建输出图像相关信息
  IplImage* dst = cvCreateImage( cvGetSize(src), src->depth, src->nChannels);
//    处理图像
  f( src, dst);

  // Show the image in the named window
//    显示图像
  cvShowImage( IMG1, dst );

  // Idle until the user hits the "Esc" key.
//    等待，直到输入了ESC键
  while( 1 ) { if( cvWaitKey( 100 ) == 27 ) break; }

  // Clean up and don’t be piggies
//    释放清除
  cvDestroyWindow( IMG1 );
  cvReleaseImage( &src );
  cvReleaseImage( &dst );

}
