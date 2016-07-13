//
// example 6-1 Hough circles
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
//
/*
You'll have to tune to detect the circles you expect
 你必须调整来找到你所想找到的圆
 //霍夫圆变换
vSeq* cvHoughCircles( 
	CvArr* image,			//Da image  8位灰度图像
	void* storage,			//Storage for sequences  序列存储器
	int method, 			//Always CV_HOUGH_GRADIENT until you, reader, invent a better method
                                这里是必填CV_HOUGH_GRADIENT的，除非你发现了更好的方法
	double dp, 				//Hough space shrinkage. a bit larger is faster, might detect better,
                                累加器图像的分辨率，如果是1，则分辨率是相同的，但是不能比1小
	double min_dist,		//Damps out multiple detection in the same area
                                为了让算法能明显区分两个不同圆之间的最小距离
   double param1=100,   //High Canny threshold (edge thresh), low is half (link finding). See Canny
                            边缘阈值，作为cvCanny的第一个参数，第二个参数为其一半
   double param2=100,   //Threshold where we declare detection in Canny space
                            作为累加器的阈值
   int min_radius=0,    //Smallest circle to find
                        找到最小圆的半径
   int max_radius=0     //Largest circle to find
                        找到最大圆的半径
  );
*/



#include <opencv/cv.h>
#include <opencv2/highgui.hpp>
#include <math.h>

//使用cvHoughCircles返回咋灰度图像中找到的圆序列
int main(int argc, char** argv) {
//    加载灰度图像
  IplImage* image = cvLoadImage(
    IMG1,
    CV_LOAD_IMAGE_GRAYSCALE
  );
//    变成更好看的彩色
 IplImage* src = cvLoadImage( IMG1 ); //Changed for prettier show in color
//    创建存储区
  CvMemStorage* storage = cvCreateMemStorage(0);
//    模糊处理，输入输出、模糊方法、水平和竖直方向sigma值
  cvSmooth(image, image, CV_GAUSSIAN, 5, 5 );
//    进行霍夫圆变换
   CvSeq* results = cvHoughCircles(
    image, 
    storage, 
    CV_HOUGH_GRADIENT, 
    4, 
    image->width/10 
  );
//    遍历结果集
  for( int i = 0; i < results->total; i++ ) {
//      返回索引制定的元素指针
    float* p = (float*) cvGetSeqElem( results, i );
//      创建圆心
    CvPoint pt = cvPoint( cvRound( p[0] ), cvRound( p[1] ) );
//      绘制圆
    cvCircle(
      src,
      pt, 
      cvRound( p[2] ),
      CV_RGB(0xff,0,0) 
    );
  }
//    显示结果
  cvNamedWindow( "cvHoughCircles", 1 );
  cvShowImage( "cvHoughCircles", src);
  cvWaitKey(0);
}

