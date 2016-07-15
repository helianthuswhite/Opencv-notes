
#include <opencv/cv.h>
#include <opencv2/highgui.hpp>
#include <math.h>

#define IMAGE "/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/images/kuaicang.jpg"

IplImage* smaller(IplImage* src);

IplImage * doPryDown(IplImage * in);

void doPerspective(IplImage*src);

IplImage* getRedChannel(IplImage* src);

//利用imageROI来增加某范围的像素
int main(int argc, char** argv)
{
    //    创建窗体
    IplImage* src;
    IplImage* dst;
    cvNamedWindow("逆透视变换", CV_WINDOW_AUTOSIZE);
    //    加载到图片
    if((src=cvLoadImage(IMAGE,1)) != 0 )
    {
//        通道分离
        dst = getRedChannel(src);
        //        修改图片大小
        dst = smaller(dst);
//        向下取样
//        dst = doPryDown(dst);
//        dst = doPryDown(dst);
        //        参数修改，写死，初始坐标x,y
//        int x = 0;
//        int y = 110;
//        //        处理部分的宽和高
//        int width = dst->width;
//        int height = dst->height/2;
//        //        需要增加的灰度值
//        int add = 100;
//        //        设置ROI
//        cvSetImageROI(dst, cvRect(x,y,width,height));
//       //        增加S通道的灰度值
//        cvAddS(dst, cvScalar(add),dst);
//        //        重新设置ROI
//        cvResetImageROI(dst);
        doPerspective(dst);
        //        显示修改后的图像
        cvShowImage( "逆透视变换",dst);
        cvWaitKey();
    }
    //    后续工作
    cvReleaseImage( &dst );
    cvDestroyWindow("逆透视变换");
    return 0;
}

IplImage* getRedChannel(IplImage* src) {
    IplImage* rImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
    IplImage* gImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
    IplImage* bImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
    cvCvtPixToPlane(src, rImg, gImg, bImg,0);
    return rImg;
}

IplImage* smaller(IplImage* src) {
    IplImage* temp;
    CvSize size;
    double scale = 0.3;     //缩放的倍数
    size.width = src->width*scale;
    size.height = src->height*scale;
    temp = cvCreateImage(size, src->depth, src->nChannels);
    cvResize(src, temp, CV_INTER_CUBIC);
    return temp;
}

IplImage * doPryDown(IplImage * in) {
//    assert(in->width%2==0 && in->height%2==0);
    IplImage * out=cvCreateImage(cvSize(in->width/2,in->height/2),in->depth,in->nChannels);
    cvPyrDown(in,out,CV_GAUSSIAN_5x5);//filter=7 目前只支持CV_GAUSSIAN_5x5
    return (out);
}

void doPerspective(IplImage*src) {
//    IplImage* dst;
    int tempx,tempy;
//    摄像机高度，单位m
    double h = 400;
//    摄像机的视角
    double alph = M_PI*5/6;
//    摄像机的坐标
    double d = 0,l = 0;
//    摄像机中心与z=0平面夹角
    double sita = M_PI/12;
//    摄像机视线投影与y轴夹角
    double gama = 0;
//    摄像机的水平和垂直像素
    int Rx = 2000,Ry = 2000;
    for( int y=0; y<src->height; y++ ) {
        //      ptr指针指向y行起始位置
        uchar* ptr1 = (uchar*) (src->imageData + y * src->widthStep);
        //      从指针中析出饱和度和高度在x维的值
        for( int x=0; x<src->width; x++ ) {
            tempy = h*atan(alph*x/(Ry - 1) - alph + sita)*sin(alph*y/(Rx - 1) - alph + gama)+d;
            tempx = h*atan(alph*x/(Ry - 1) - alph + sita)*cos(alph*y/(Rx - 1) - alph + gama)+l;
    
            uchar* ptr2 = (uchar*) (src->imageData + tempy * src->widthStep);
            ptr1[x] = ptr2[tempx];
        }
    }
}


