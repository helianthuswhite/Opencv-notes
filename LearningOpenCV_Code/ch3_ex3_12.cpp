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
// ch3_ex3_12 image_name x y width height add#

//利用imageROI来增加某范围的像素
int main(int argc, char** argv)
{
//    创建窗体
    IplImage* src;
    cvNamedWindow("Example3_12_pre", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Example3_12_post", CV_WINDOW_AUTOSIZE);
//    加载到图片
    if((src=cvLoadImage(IMG1,1)) != 0 )
    {
//        参数修改，写死，初始坐标x,y
		int x = 0;
		int y = 0;
//        处理部分的宽和高
		int width = 200;
		int height = 200;
//        需要增加的灰度值
		int add = 100;
//        显示图片
		cvShowImage( "Example3_12_pre", src);
//        设置ROI
		cvSetImageROI(src, cvRect(x,y,width,height));
//        增加S通道的灰度值
		cvAddS(src, cvScalar(add),src);
//        重新设置ROI
		cvResetImageROI(src);
//        显示修改后的图像
		cvShowImage( "Example3_12_post",src);
      cvWaitKey();
    }
//    后续工作
  cvReleaseImage( &src );
  cvDestroyWindow("Example3_12_pre");
  cvDestroyWindow("Example3_12_post");   
    return 0;
}
