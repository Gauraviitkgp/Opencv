#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <math.h>
using namespace cv;
using namespace std;

int i,j,t,p;

void displayimage(Mat image, String windowname){
    
    imshow(windowname, image);
}


Mat readimage(String filename)
{
    return imread(filename);
}

Mat calibrate(Mat img)
{
  Mat img2(img.rows,img.cols,CV_8UC3,255);
  float x,y,z;
  float a,b;
  float D,Dr;
  a=x/z; b=y/z;
  r*r=a*a+b*b;
  D=a*tan(r);
  Dr=D(1+)
}




int main(int argc, char** argv)
{
    Mat image=imread(argv[1],CV_LOAD_IMAGE_COLOR);
    calibrate(image);
    imshow("ima",image);
    waitKey(0);
    return 0;
}
