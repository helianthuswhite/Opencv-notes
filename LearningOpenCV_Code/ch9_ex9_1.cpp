//
// Example 9-1. Reading out the RGB values of all pixels in one row of a video and accumulating those
//              values into three separate files
//
// STORE TO DISK A LINE SEGMENT OF BGR PIXELS FROM pt1 to pt2.  
//…
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

#include <stdio.h>
#include <opencv/cv.h>
#include <opencv2/highgui.hpp>

void help() {
printf("\nRead out RGB pixel values and store them to disk\nCall:\n"
"./ch9_ex9_1 avi_file\n"
"\n This will store to files blines.csv, glines.csv and rlines.csv\n\n");
}

//从视频中读出所有像素的RGB的值，并将其分为三个文件
int main( int argc, char** argv  )
{
//    if(argc != 2) {help(); return -1;}
//    读取视频
    cvNamedWindow( "Example9_1", CV_WINDOW_AUTOSIZE );
    CvCapture* capture = cvCreateFileCapture( VIDEO2 );
	if(!capture) {printf("\nCouldn't open %s\n",VIDEO2); help(); return -1;}
//    设置采样线段的端点
    CvPoint pt1 = cvPoint(10,10);
    CvPoint pt2 = cvPoint(20,20);
    int max_buffer;
    IplImage *rawImage;
    int r[10000],g[10000],b[10000];
//    打开文件
    FILE *fptrb = fopen("blines.csv","w"); //Store the data here
    FILE *fptrg = fopen("glines.csv","w"); // for each color channel
    FILE *fptrr = fopen("rlines.csv","w");
    CvLineIterator iterator;
    //MAIN PROCESSING LOOP:
    for(;;){
        if( !cvGrabFrame( capture ))
              break;
//        抓取视频图像的指针
        rawImage = cvRetrieveFrame( capture );
//        线采样函数进行采样
        max_buffer = cvInitLineIterator(rawImage,pt1,pt2,&iterator,8,0);
//        显示抓取的图像
        cvShowImage( "Example9_1", rawImage );
        int c = cvWaitKey(10);
//        将数据写入文件
        for(int j=0; j<max_buffer; j++){
            fprintf(fptrb,"%d,", iterator.ptr[0]); //Write blue value
            fprintf(fptrg,"%d,", iterator.ptr[1]); //green
            fprintf(fptrr,"%d,", iterator.ptr[2]); //red
            iterator.ptr[2] = 255;  //Mark this sample in red
//            步入下一个像素
            CV_NEXT_LINE_POINT(iterator); //Step to the next pixel
        }
        //OUTPUT THE DATA IN ROWS:
//        按行输出数据
        fprintf(fptrb,"\n");fprintf(fptrg,"\n");fprintf(fptrr,"\n");
    }
    //CLEAN UP:
//    清理战场
    printf("\nData stored to files: blines.csv, glines.csv and rlines.csv\n\n");
    fclose(fptrb); fclose(fptrg); fclose(fptrr);
    cvReleaseCapture( &capture );
    cvDestroyWindow( "Example9_1" );
}
