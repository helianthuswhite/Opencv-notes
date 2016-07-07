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

#include "opencv/cv.h"
#include <stdio.h>

//通过简单的CV_MAT_ELEM宏存取矩阵
int main()
{
//    创建矩阵，传入行数和列数以及数据类型
  CvMat* mat = cvCreateMat( 5, 5, CV_32FC1 );
//    获取到矩阵的元素，参数为矩阵、元素类型、行数和列数
  float element_3_2 = CV_MAT_ELEM( *mat, float, 3, 2 );
  printf("Exercise 3_4, matrix created and accessed [3,2]=%f\n",element_3_2);
}
