//
//Example 6-2. An affine transformation
// Usage: warp_affine <image>
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

// warp_affine <image>
#include <opencv/cv.h>
#include <opencv2/highgui.hpp>
#define affine 
#ifdef affine

//仿射变换
int main(int argc, char** argv)
{
//    创建两个矩阵的三元数组
   CvPoint2D32f srcTri[3], dstTri[3];
//    创建矩阵
   CvMat* rot_mat = cvCreateMat(2,3,CV_32FC1);
   CvMat* warp_mat = cvCreateMat(2,3,CV_32FC1);
   IplImage *src, *dst;
//    加载图像成功后执行
    if((src=cvLoadImage(IMG1,1)) != 0 )
    {
//        复制图像
   dst = cvCloneImage(src);
//        设置原点
   dst->origin = src->origin;
//        初始化元素值
   cvZero(dst);

   //COMPUTE WARP MATRIX
//        计算变换坐标
   srcTri[0].x = 0;          //src Top left 原矩阵左上角
   srcTri[0].y = 0;
   srcTri[1].x = src->width - 1;    //src Top right 原矩阵右上角
   srcTri[1].y = 0;
   srcTri[2].x = 0;          //src Bottom left  原矩阵左下角
   srcTri[2].y = src->height - 1;
   //- - - - - - - - - - - - - - -//
   dstTri[0].x = src->width*0.0;    //dst Top left 目标左上角
   dstTri[0].y = src->height*0.33;
   dstTri[1].x = src->width*0.85; //dst Top right  目标右上角
   dstTri[1].y = src->height*0.25;
   dstTri[2].x = src->width*0.15; //dst Bottom left  目标左下角
   dstTri[2].y = src->height*0.7;
//        生成仿射映射矩阵 ，参数为：两个包含三个点的数组，需要进行仿射变换的矩阵
   cvGetAffineTransform(srcTri,dstTri,warp_mat);
//        进行仿射变换
   cvWarpAffine(src,dst,warp_mat);
   cvCopy(dst,src);

   //COMPUTE ROTATION MATRIX
//        创建旋转矩阵
   CvPoint2D32f center = cvPoint2D32f(src->width/2,
                                         src->height/2);
//        设定旋转参数
   double angle = -50.0;
   double scale = 0.6;
//        生成旋转的映射矩阵
   cv2DRotationMatrix(center,angle,scale,rot_mat);
//        进行仿射变换
   cvWarpAffine(src,dst,rot_mat);

   //DO THE TRANSFORM:
//        显示结果
   cvNamedWindow( "Affine_Transform", 1 );
      cvShowImage( "Affine_Transform", dst );
      cvWaitKey();
    }
//    释放内存
   cvReleaseImage(&dst);
   cvReleaseMat(&rot_mat);
   cvReleaseMat(&warp_mat);
    return 0;
}
#endif
