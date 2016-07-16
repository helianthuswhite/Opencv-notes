// Calibrate from a list of images
//
// console application.
// Gary Bradski April'08
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

#include <opencv/cv.h>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include <stdlib.h>

int n_boards = 0; //Will be set by input list
const int board_dt = 10;
int board_w;
int board_h;

//从磁盘中获得图像进行校准
void help(){
	printf("Calibration from disk. Call convention:\n\n"
			"  ch11_ex11_1_fromdisk board_w board_h image_list\n\n"
			"Where: board_{w,h} are the # of internal corners in the checkerboard\n"
			"       width (board_w) and height (board_h)\n"
			"       image_list is space separated list of path/filename of checkerboard\n"
			"       images\n\n"
			"Hit 'p' to pause/unpause, ESC to quit.  After calibration, press any other key to step through the images\n\n");
}

int main(int argc, char* argv[]) {
  
  CvCapture* capture;// = cvCreateCameraCapture( 0 );
 // assert( capture );
//    修改一波输入参数
//	if(argc != 4){
//		help();
//		return -1;
//	}
	help();
	board_w = 12;
	board_h = 12;
	int board_n  = board_w * board_h;
	CvSize board_sz = cvSize( board_w, board_h );
	FILE *fptr = fopen("/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/LearningOpenCV_Code/ch11_chessboards.txt","r");
	char names[2048];
	//COUNT THE NUMBER OF IMAGES:
//    获得图片名称
	while(fscanf(fptr,"%s ",names)==1){
		n_boards++;
	}
	rewind(fptr);

  cvNamedWindow( "Calibration" );
  //ALLOCATE STORAGE
//    分配内存，标定参数的创建
  CvMat* image_points      = cvCreateMat(n_boards*board_n,2,CV_32FC1);
  CvMat* object_points     = cvCreateMat(n_boards*board_n,3,CV_32FC1);
  CvMat* point_counts      = cvCreateMat(n_boards,1,CV_32SC1);

///  CvMat * image_points	= cvCreateMat(1, n_boards*board_n, CV_32FC2);
///  CvMat * object_points = cvCreateMat(1, n_boards*board_n, CV_32FC3);
///  CvMat * point_counts  = cvCreateMat(1, n_boards, CV_32SC1);
  
  CvMat* intrinsic_matrix  = cvCreateMat(3,3,CV_32FC1);
  CvMat* distortion_coeffs = cvCreateMat(4,1,CV_32FC1);

//    创建图像参数，用与获取磁盘中图像
  IplImage* image = 0;// = cvQueryFrame( capture );
  IplImage* gray_image = 0; //for subpixel
  CvPoint2D32f* corners = new CvPoint2D32f[ board_n ];
  int corner_count;
  int successes = 0;
  int step;
//    获取磁盘中文件图像
  for( int frame=0; frame<n_boards; frame++ ) {
	  fscanf(fptr,"%s ",names);

	  if(image){
		  cvReleaseImage(&image);
		  image = 0;
	  }
	  image = cvLoadImage( names);
	  if(gray_image == 0  && image) //We'll need this for subpixel accurate stuff
//          为了获得亚像素角点
		  gray_image = cvCreateImage(cvGetSize(image),8,1);

	  if(!image)
		  printf("null image\n");
//      寻找棋盘角点
      int found = cvFindChessboardCorners(
        image,
        board_sz,
        corners,
        &corner_count, 
        CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
      );

	  //Get Subpixel accuracy on those corners
//      寻找亚像素角点
	  cvCvtColor(image, gray_image, CV_BGR2GRAY);
	  cvFindCornerSubPix(gray_image, corners, corner_count, 
			  cvSize(11,11),cvSize(-1,-1), cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
	  //Draw it
//      绘制出所有的角点
	  cvDrawChessboardCorners(image, board_sz, corners, corner_count, found);
      cvShowImage( "Calibration", image );

      // If we got a good board, add it to our data
      //如果获得合适的板，将其添加入我们的数据中
      if( corner_count == board_n ) {
		  step = successes*board_n;
//	printf("Found = %d for %s\n",found,names);
        for( int i=step, j=0; j<board_n; ++i,++j ) {
 ///         CV_MAT_ELEM(*image_points, CvPoint2D32f,0,i) = cvPoint2D32f(corners[j].x,corners[j].y);
 ///         CV_MAT_ELEM(*object_points,CvPoint3D32f,0,i) = cvPoint3D32f(j/board_w, j%board_w, 0.0f);
          CV_MAT_ELEM(*image_points, float,i,0) = corners[j].x;
          CV_MAT_ELEM(*image_points, float,i,1) = corners[j].y;
          CV_MAT_ELEM(*object_points,float,i,0) = j/board_w;
          CV_MAT_ELEM(*object_points,float,i,1) = j%board_w;
          CV_MAT_ELEM(*object_points,float,i,2) = 0.0f;
 		
		}
//        CV_MAT_ELEM(*point_counts, int,0,successes) = board_n;
         CV_MAT_ELEM(*point_counts, int,successes,0) = board_n;		
       successes++;
      }
      
 //    if( successes == n_boards ) break;
//      P键暂停，ESC退出
    int c = cvWaitKey(15);
	if(c == 'p') {
		c = 0;
		while(c != 'p' && c != 27){
			c = cvWaitKey(250);
		}
	}
	if(c == 27)
		return 0;
  }
	printf("successes = %d, n_boards=%d\n",successes,n_boards);
  //ALLOCATE MATRICES ACCORDING TO HOW MANY IMAGES WE FOUND CHESSBOARDS ON
///  CvMat* image_points2      = cvCreateMat(1,successes*board_n,CV_32FC2);
///  CvMat* object_points2     = cvCreateMat(1,successes*board_n,CV_32FC3);
///  CvMat* point_counts2      = cvCreateMat(1,successes,CV_32SC1);
//    根据找到的棋盘分配矩阵
  CvMat* object_points2     = cvCreateMat(successes*board_n,3,CV_32FC1);
  CvMat* image_points2      = cvCreateMat(successes*board_n,2,CV_32FC1);
  CvMat* point_counts2      = cvCreateMat(successes,1,CV_32SC1);
  //TRANSFER THE POINTS INTO THE CORRECT SIZE MATRICES
//    把所有的点转变成合适大小的矩阵
  for(int i = 0; i<successes*board_n; ++i){
///      CV_MAT_ELEM(*image_points2, CvPoint2D32f,0,i)  = CV_MAT_ELEM(*image_points, CvPoint2D32f,0,i);
///      CV_MAT_ELEM(*object_points2,CvPoint3D32f,0,i)  = CV_MAT_ELEM(*object_points,CvPoint3D32f,0,i);
	  	  CV_MAT_ELEM(*image_points2, float,i,0) 	=	CV_MAT_ELEM(*image_points, float,i,0);
          CV_MAT_ELEM(*image_points2, float,i,1) 	= 	CV_MAT_ELEM(*image_points, float,i,1);
          CV_MAT_ELEM(*object_points2,float,i,0) = CV_MAT_ELEM(*object_points,float,i,0) ;
          CV_MAT_ELEM(*object_points2,float,i,1) = CV_MAT_ELEM(*object_points,float,i,1) ;
          CV_MAT_ELEM(*object_points2,float,i,2) = CV_MAT_ELEM(*object_points,float,i,2) ;
 
  } 
  for(int i=0; i<successes; ++i){
///		CV_MAT_ELEM(*point_counts2,int,0, i) = CV_MAT_ELEM(*point_counts, int,0,i);
 		CV_MAT_ELEM(*point_counts2,int,i, 0) = CV_MAT_ELEM(*point_counts, int,i,0);
  }
  cvReleaseMat(&object_points);
  cvReleaseMat(&image_points);
  cvReleaseMat(&point_counts);

 // cvWaitKey();//Now we have to reallocate the matrices
 // return 0;
  // At this point we have all of the chessboard corners we need.
  //
  
    // Initialize the intrinsic matrix such that the two focal
    // lengths have a ratio of 1.0
    //在这里我们已经获得我们所需要的所有角点了
    //    接着我们要初始化机内参数矩阵使得两个焦距长度比率为1.0
    CV_MAT_ELEM( *intrinsic_matrix, float, 0, 0 ) = 1.0f;
    CV_MAT_ELEM( *intrinsic_matrix, float, 1, 1 ) = 1.0f;
printf("cvCalibrateCamera2\n");
//    矫正一波
    cvCalibrateCamera2(
      object_points2,
      image_points2,
      point_counts2,
      cvGetSize( image ),
      intrinsic_matrix,
      distortion_coeffs,
      NULL,
      NULL,
      0//CV_CALIB_FIX_ASPECT_RATIO
    );
  // Save our work
//    保存我们获得的参数
  cvSave("/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/LearningOpenCV_Code/Intrinsics.xml",intrinsic_matrix);
  cvSave("/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/LearningOpenCV_Code/Distortion.xml",distortion_coeffs);
  // Load test
//    加载测试
  CvMat *intrinsic = (CvMat*)cvLoad("/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/LearningOpenCV_Code/Intrinsics.xml");
  CvMat *distortion = (CvMat*)cvLoad("/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/LearningOpenCV_Code/Distortion.xml");

  // Build the undistort map which we will use for all 
  // subsequent frames.
  //创建和初始化map
  IplImage* mapx = cvCreateImage( cvGetSize(image), IPL_DEPTH_32F, 1 );
  IplImage* mapy = cvCreateImage( cvGetSize(image), IPL_DEPTH_32F, 1 );
  printf("cvInitUndistortMap\n");
  cvInitUndistortMap(
    intrinsic,
    distortion,
    mapx,
    mapy
  );
  // Just run the camera to the screen, now only showing the undistorted
  // image.
  //运行一波比较一下结果
  rewind(fptr);
  cvNamedWindow( "Undistort" );
  printf("\n\nPress any key to step through the images, ESC to quit\n\n");
  while(fscanf(fptr,"%s ",names)==1){
//      释放打开的文件指针
	  if(image){
		  cvReleaseImage(&image);
		  image = 0;
	  }
//      加载图像并显示结果
	  image = cvLoadImage( names);
	  IplImage *t = cvCloneImage(image);
      cvShowImage( "Calibration", image );
      cvRemap( t, image, mapx, mapy );
	  cvReleaseImage(&t);
//	  cvUndistort2(
	  cvShowImage("Undistort", image);
    if((cvWaitKey()&0x7F) == 27) break;  
  }

  return 0;
} 
