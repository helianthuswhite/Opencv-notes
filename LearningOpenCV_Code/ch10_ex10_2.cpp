// Example 10-2. Kalman filter sample code
//
//  Use Kalman Filter to model particle in circular trajectory.
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
#include "opencv/cv.h"
#include "opencv2/highgui.hpp"
#include "cvx_defs.h"

//将汽车位置从角度转换为笛卡尔坐标的矩阵
#define phi2xy(mat)                                                  \
  cvPoint( cvRound(img->width/2 + img->width/3*cos(mat->data.fl[0])),\
    cvRound( img->height/2 - img->width/3*sin(mat->data.fl[0])) )

//Kalman滤波器显示汽车运动
int main(int argc, char** argv) {

    // Initialize, create Kalman Filter object, window, random number
    // generator etc.
    //初始化，创建滤波器对象，窗体和随机数
    cvNamedWindow( "Kalman", 1 );
    CvRandState rng;
//    生成随机数，参数：数据结构，下界，上界，分布参数，分布类型
    cvRandInit( &rng, 0, 1, -1, CV_RAND_UNI );
//    创建用于绘制的图像以及滤波器结构
    IplImage* img = cvCreateImage( cvSize(500,500), 8, 3 );
    CvKalman* kalman = cvCreateKalman( 2, 1, 0 );
    // state is (phi, delta_phi) - angle and angular velocity
    // Initialize with random guess.
    //创建状态并初始化，将其初始化为分布在0附近的合理的随机数
    CvMat* x_k = cvCreateMat( 2, 1, CV_32FC1 );
    cvRandSetRange( &rng, 0, 0.1, 0 );
    rng.disttype = CV_RAND_NORMAL;
    cvRand( &rng, x_k );

    // process noise
    //创建过程噪声
    CvMat* w_k = cvCreateMat( 2, 1, CV_32FC1 );
    
    // measurements, only one parameter for angle
    //创建测量值矩阵
    CvMat* z_k = cvCreateMat( 1, 1, CV_32FC1 );
    cvZero( z_k );

    // Transition matrix 'F' describes relationship between
    // model parameters at step k and at step k+1 (this is 
    // the "dynamics" in our model.
    //创建传递矩阵；传递矩阵联系着时间t到t+1的状态
    const float F[] = { 1, 1, 0, 1 };
    memcpy( kalman->transition_matrix->data.fl, F, sizeof(F));
    // Initialize other Kalman filter parameters.
    //初始化Kalman滤波器
    cvSetIdentity( kalman->measurement_matrix,    cvRealScalar(1) );
    cvSetIdentity( kalman->process_noise_cov,     cvRealScalar(1e-5) );
    cvSetIdentity( kalman->measurement_noise_cov, cvRealScalar(1e-1) );
    cvSetIdentity( kalman->error_cov_post,        cvRealScalar(1));

    // choose random initial state
    //随机初始化后验状态
    cvRand( &rng, kalman->state_post );

    while( 1 ) {
        // predict point position
//        预测点的位置
        const CvMat* y_k = cvKalmanPredict( kalman, 0 );

        // generate measurement (z_k)
        //操作产生新的测量值
        cvRandSetRange( 
            &rng, 
            0, 
            sqrt(kalman->measurement_noise_cov->data.fl[0]), 
            0 
        );
        cvRand( &rng, z_k );
//        由x_k乘以测量矩阵加上随机测量噪声得出
        cvMatMulAdd( kalman->measurement_matrix, x_k, z_k, z_k );
        // plot points (eg convert to planar co-ordinates and draw)
        //绘制出合成的观测值、滤波器预测的位置和基本状态三个点
        cvZero( img );
        cvCircle( img, phi2xy(z_k), 4, CVX_YELLOW );   // observed state
        cvCircle( img, phi2xy(y_k), 4, CVX_WHITE, 2 ); // "predicted" state
        cvCircle( img, phi2xy(x_k), 4, CVX_RED );      // real state
        cvShowImage( "Kalman", img );
        // adjust Kalman filter state
        //调整滤波器的测量值
        cvKalmanCorrect( kalman, z_k );

        // Apply the transition matrix 'F' (eg, step time forward)
        // and also apply the "process" noise w_k.
        //由x_k乘以时间传递矩阵完成新的迭代并加上新产生的噪声，开始循环迭代
        cvRandSetRange( 
            &rng, 
            0, 
            sqrt(kalman->process_noise_cov->data.fl[0]), 
            0 
            );
        cvRand( &rng, w_k );
        cvMatMulAdd( kalman->transition_matrix, x_k, w_k, x_k );
        
        // exit if user hits 'Esc'
//        ESC键退出
        if( cvWaitKey( 100 ) == 27 ) break;
    }

    return 0;
}
