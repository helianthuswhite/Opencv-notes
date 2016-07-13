
//
// Example 6-5. Use of cvDFT() to accelerate the computation of convolutions
// Use DFT to accelerate the convolution of array A by kernel B.
// Place the result in array V.
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

#include <opencv/cv.h>
#include <opencv2/highgui.hpp>

//利用cvDFT加快卷积的计算
int main(int argc, char** argv)
{
    int M1 = 2;
    int M2 = 2;
    int N1 = 2;
    int N2 = 2;
    // initialize A and B
    //创建矩阵A和B
    CvMat* A = cvCreateMat( M1, N1, CV_32F );
    CvMat* B = cvCreateMat( M2, N2, A->type );

    // it is also possible to have only abs(M2-M1)+1×abs(N2-N1)+1
    // part of the full convolution result
//    可以让abs(M2-M1)+1×abs(N2-N1)+1作为卷积结果的一部分
    CvMat* conv = cvCreateMat(
      A->rows+B->rows-1,
      A->cols+B->cols-1,
      A->type
    );
    
//    对于给定的矢量尺寸返回最优DFT尺寸
    int dft_M = cvGetOptimalDFTSize( A->rows+B->rows-1 );
    int dft_N = cvGetOptimalDFTSize( A->cols+B->cols-1 );
    
//    创建DFT矩阵
    CvMat* dft_A = cvCreateMat( dft_M, dft_N, A->type );
    CvMat* dft_B = cvCreateMat( dft_M, dft_N, B->type );
    CvMat tmp;

    // copy A to dft_A and pad dft_A with zeros
    //把A复制到dft_A并且对A初始化为0
    cvGetSubRect( dft_A, &tmp, cvRect(0,0,A->cols,A->rows));
    cvCopy( A, &tmp );
    cvGetSubRect( 
      dft_A,
      &tmp,
      cvRect( A->cols, 0, dft_A->cols-A->cols, A->rows )
    );
    cvZero( &tmp );

    // no need to pad bottom part of dft_A with zeros because of
    // use nonzero_rows parameter in cvDFT() call below
    //利用cvDFT进行变换
    cvDFT( dft_A, dft_A, CV_DXT_FORWARD, A->rows );

    // repeat the same with the second array
    //重复同样的操作
    cvGetSubRect( dft_B, &tmp, cvRect(0,0,B->cols,B->rows) );
    cvCopy( B, &tmp );
    cvGetSubRect(
      dft_B, 
      &tmp, 
      cvRect( B->cols, 0, dft_B->cols-B->cols, B->rows )
    );
    cvZero( &tmp );

    // no need to pad bottom part of dft_B with zeros because of
    // use nonzero_rows parameter in cvDFT() call below
    //重复。。。。。。。
    cvDFT( dft_B, dft_B, CV_DXT_FORWARD, B->rows );

    // or CV_DXT_MUL_CONJ to get correlation rather than convolution 
    //进行频谱乘法运算
    cvMulSpectrums( dft_A, dft_B, dft_A, 0 );

    // calculate only the top part
//    /只计算顶部的部分
    cvDFT( dft_A, dft_A, CV_DXT_INV_SCALE, conv->rows );
    cvGetSubRect( dft_A, &tmp, cvRect(0,0,conv->cols,conv->rows) );
    
    cvCopy( &tmp, conv );
}

