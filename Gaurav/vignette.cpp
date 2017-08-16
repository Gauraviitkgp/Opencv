#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <math.h>

using namespace cv;
using namespace std;


void displayimage(Mat image, String windowname){
    
    imshow(windowname, image);
}


Mat readimage(String filename)
{
    return imread(filename);
}

float dist(int i,int j,Mat image)
{
  return pow(((i-(image.rows/2))*(i-(image.rows/2))+(j-(image.cols/2))*(j-(image.cols/2))),1);
}

float dista(int i,int j,Mat image)
{
  return pow(((i-(image.rows/2))*(i-(image.rows/2))+(j-(image.cols/2))*(j-(image.cols/2))),0.10);
}

void vignette(Mat image)
{
  int factor=10;
  int i,j,k;
  Mat temp(image.rows,image.cols,CV_8UC3,255);
  for(i=0;i<image.rows;i++)
    {
      for(j=0;j<image.cols;j++)
	{
	  for(k=0;k<3;k++)
	    {	      
	     
	      temp.at<Vec3b>(i,j)[k]=(image.at<Vec3b>(i,j)[k])*(1-(dist(i,j,image)/dist(0,0,image)));
	      image.at<Vec3b>(i,j)[k]*=(1-(dista(i,j,image)/dista(0,0,image)));
	    }
	}
    }
  imshow("Image",image);
  imshow("Temp",temp);
}




int main(int argc, char** argv)
{
       
    Mat image=imread(argv[1],CV_LOAD_IMAGE_COLOR);
    vignette(image);
    waitKey(0);
    return 0;
}

