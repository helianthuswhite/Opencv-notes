
#include <opencv/cv.h>
#include <opencv2/highgui.hpp>

#define IMAGE "/Users/W_littlewhite/Documents/Xcode Project/Xcode Project/images/kuaicang.jpg"

IplImage* smaller(IplImage* src);

IplImage * doPryDown(IplImage * in);

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
//        修改图片大小
        dst = smaller(src);
//        向下取样
        dst = doPryDown(dst);
        dst = doPryDown(dst);
        //        参数修改，写死，初始坐标x,y
        int x = 0;
        int y = 110;
        //        处理部分的宽和高
        int width = dst->width;
        int height = dst->height/2;
        //        需要增加的灰度值
        int add = 100;
        //        设置ROI
        cvSetImageROI(dst, cvRect(x,y,width,height));
       //        增加S通道的灰度值
        cvAddS(dst, cvScalar(add),dst); 
        //        重新设置ROI
        cvResetImageROI(dst);
        //        显示修改后的图像
        cvShowImage( "逆透视变换",dst);
        cvWaitKey();
    }
    //    后续工作
    cvReleaseImage( &dst );
    cvDestroyWindow("逆透视变换");
    return 0;
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