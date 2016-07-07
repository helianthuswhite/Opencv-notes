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

// ch3_ex3_13 image_name x y width height add# 

//利用widthStep方法将所有的像素值增加1
int main(int argc, char** argv)
{
//    加载图片
    IplImage* interest_img;
    CvRect interest_rect;
    if((interest_img=cvLoadImage(IMG1,1)) != 0 )
    {
//        参数修改
        interest_rect.x = 100;
        interest_rect.y = 100;
        interest_rect.width = 200;
        interest_rect.height = 200;
        int add = 100;

        // Assuming IplImage *interest_img; and 
        //  CvRect interest_rect;
        //  Use widthStep to get a region of interest
        //
        // (Alternate method)
        //创建新的图像头
        IplImage *sub_img = cvCreateImageHeader(
          cvSize(
             interest_rect.width, 
             interest_rect.height
          ),
          interest_img->depth, 
          interest_img->nChannels
        );
//        设定相同的初始位置
        sub_img->origin = interest_img->origin;
//        设定相同的行距
        sub_img->widthStep = interest_img->widthStep;
//        设置选取区域的头指针
        sub_img->imageData = interest_img->imageData +
          interest_rect.y * interest_img->widthStep  +
          interest_rect.x * interest_img->nChannels;
//        更改选取区域的图片
        cvAddS( sub_img, cvScalar(add), sub_img );
//        释放头指针
        cvReleaseImageHeader(&sub_img);
//        后续工作
        cvNamedWindow( "Roi_Add", CV_WINDOW_AUTOSIZE );
        cvShowImage( "Roi_Add", interest_img );
        cvWaitKey();
    }
    return 0;
}

