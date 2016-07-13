//
// Example 7-1. Histogram computation and display
//
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
//
//

#include <opencv/cv.h>
#include <opencv2/highgui.hpp>

//直方图的计算与显示
int main( int argc, char** argv ) {

    IplImage* src;
    
//    如果成功加载图像
    if( (src=cvLoadImage(IMG1, 1))!= 0) {

        // Compute the HSV image, and decompose it into separate planes.
//        创建一个HSV图像
        IplImage* hsv = cvCreateImage( cvGetSize(src), 8, 3 );
        cvCvtColor( src, hsv, CV_BGR2HSV );

//        分别创建单通道图像部分
        IplImage* h_plane  = cvCreateImage( cvGetSize(src), 8, 1 );
        IplImage* s_plane  = cvCreateImage( cvGetSize(src), 8, 1 );
        IplImage* v_plane  = cvCreateImage( cvGetSize(src), 8, 1 );
        IplImage* planes[] = { h_plane, s_plane };
//        分割HSV图像到各个单通道
        cvCvtPixToPlane( hsv, h_plane, s_plane, v_plane, 0 );

        // Build the histogram and compute its contents.
        //创建直方图
        int h_bins = 30, s_bins = 32; 
        CvHistogram* hist;
        {
          int    hist_size[] = { h_bins, s_bins };
          float  h_ranges[]  = { 0, 180 };          // hue is [0,180]
          float  s_ranges[]  = { 0, 255 }; 
          float* ranges[]    = { h_ranges, s_ranges };
//            创建新的直方图，参数分别为：直方图包含的维数，对应维数的bin的个数，存储类型，取值范围，bin是否均匀
          hist = cvCreateHist(
            2, 
            hist_size, 
            CV_HIST_ARRAY, 
            ranges, 
            1 
          ); 
        }
//        从图像中计算直方图
        cvCalcHist( planes, hist, 0, 0 );

        // Create an image to use to visualize our histogram.
        //创建一个新的图像来可视化我们的直方图
        int scale = 10;
        IplImage* hist_img = cvCreateImage(  
          cvSize( h_bins * scale, s_bins * scale ), 
          8, 
          3
        ); 
        cvZero( hist_img );

        // populate our visualization with little gray squares.
        //填充我们的直方图
        float max_value = 0;
//        获取最大值
        cvGetMinMaxHistValue( hist, 0, &max_value, 0, 0 );

//        循环绘制直方图
        for( int h = 0; h < h_bins; h++ ) {
            for( int s = 0; s < s_bins; s++ ) {
//                访问直方图数据
                float bin_val = cvQueryHistValue_2D( hist, h, s );
//                转换数据与颜色对应
                int intensity = cvRound( bin_val * 255 / max_value );
                cvRectangle( 
                  hist_img, 
                  cvPoint( h*scale, s*scale ),
                  cvPoint( (h+1)*scale - 1, (s+1)*scale - 1),
                  CV_RGB(intensity,intensity,intensity), 
                  CV_FILLED
                );
            }
        }
//        显示结果
        cvNamedWindow( "Source", 1 );
        cvShowImage(   "Source", src );

        cvNamedWindow( "H-S Histogram", 1 );
        cvShowImage(   "H-S Histogram", hist_img );

        cvWaitKey(0);
    }
}

