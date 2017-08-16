#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

int x;

void displayimage(Mat image, String windowname){
    
    imshow(windowname, image);
}


Mat readimage(String filename)
{
    return imread(filename);
}

Mat morph(Mat img1, Mat img2)
{
  Mat temp(img1.rows,img2.rows,CV_8UC3,Scalar(255,255,255));
  int i,j,k;
  for(i=0;i<temp.rows;i++)
    {
      for(j=0;j<temp.cols;j++)
	{
	  for(k=0;k<3;k++)
	    {
	      temp.at<Vec3b>(i,j)[k]=(((float)x/100)*img1.at<Vec3b>(i,j)[k])+((1-((float) x)/100)*img2.at<Vec3b>(i,j)[k]);
	    }
	}
    }
  return temp;
}




int main(int argc, char** argv){
  Mat img1=imread(argv[1],CV_LOAD_IMAGE_COLOR);
  Mat img2=imread(argv[2],CV_LOAD_IMAGE_COLOR);
  namedWindow("morph",WINDOW_NORMAL);
  createTrackbar("t","morph",&x,100);
  while(1)
    {
      imshow("morph",morph(img1,img2));
      waitKey(5);
    }
  return 0;
}

