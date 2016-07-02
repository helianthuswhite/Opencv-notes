#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#define IMG1 "/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/images/test_img.png"

#define IMG2 "/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/images/test_img2.png"

int main( int argc, char** argv )
{
    IplImage* img = cvLoadImage(IMG2);
    cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE );
    cvShowImage("Example1", img );
    cvWaitKey(0);
    cvReleaseImage( &img );
    cvDestroyWindow("Example1");
}
