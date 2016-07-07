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

// alphablend <imageA> <image B> <x> <y> <width> <height> 
//            <alpha> <beta>
#include <opencv/cv.h>
#include <opencv2/highgui.hpp>
#include <stdio.h>

//通过alpha将src2融合到src1
int main(int argc, char** argv)
{
//    加载图片
    IplImage *src1, *src2;
    if( ((src1=cvLoadImage(IMG1,1)) != 0)&&((src2=cvLoadImage(IMG2,1)) != 0 ))
    {
//        修改参数
        int x = 100;
        int y = 100;
        int width = 200;
        int height = 200;
//        融合度修改，alpha为src1融合度，beta为src2融合度，两者之和大于0小于1
        double alpha = 0.1;
        double beta  = 0.8;
//        分别设置两个图像的ROI
        cvSetImageROI(src1, cvRect(x,y,width,height));
        cvSetImageROI(src2, cvRect(0,0,width,height));
//        开始进行融合
        cvAddWeighted(src1, alpha, src2, beta,0.0,src1);
//        刷新src1的ROI
        cvResetImageROI(src1);
//        显示结果
        cvNamedWindow( "Alpha_blend", 1 );
        cvShowImage( "Alpha_blend", src1 );
        cvWaitKey();
    }
    else 
      printf("Couldn't load one or both of %s, %s\n",argv[1],argv[2]);
    return 0;
}
