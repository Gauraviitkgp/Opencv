#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

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

void histogram(Mat image)
{
  int a[255]={0},i,t,j,max=-1;
  Mat temp(500,255,CV_8UC1);
  for(i=0;i<512;i++)
    {
      for(j=0;j<512;j++)
	{
	  t=image.at<uchar>(i,j);
	  a[t]++;
	  if(a[t]>max)
	   max=a[t];
	}
    }
  for(i=0;i<255;i++)
    {
      a[i]=(a[i]*500)/max;
    }
  for(i=0;i<255;i++)
    {
      for(j=499;j>-1;j--)
	{
	  if(a[i]!=0)
	    {
	      temp.at<uchar>(j,i)=255;
	      a[i]--;
	    }
	  else
	    {
	      temp.at<uchar>(j,i)=0;
	    }
	}
    }
  displayimage(temp,"Temp");
}

int main(int argc, char** argv){
       
    Mat image=imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
    histogram(image);
    waitKey(0);
    return 0;
}

