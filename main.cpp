#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#define IMG1 "/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/LearningOpenCV_Code/HandOutdoorColor.jpg"

#define IMG2 "/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/LearningOpenCV_Code/fruits.jpg"

#define VIDEO "/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/LearningOpenCV_Code/test.avi"

int main( int argc, char** argv ) {
    cvNamedWindow( "Example2", CV_WINDOW_AUTOSIZE );
    CvCapture* capture = cvCaptureFromAVI( argv[1] ); // either one will work
//    CvCapture* capture = cvCreateFileCapture(VIDEO);
    IplImage* frame;
    while(1) {
        frame = cvQueryFrame( capture );
        if( !frame ) break;
        cvShowImage( "Example2", frame );
        char c = cvWaitKey(33);
        if( c == 27 ) break;
    }
    cvReleaseCapture( &capture );
    cvDestroyWindow( "Example2" );
}
