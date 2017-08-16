#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

float a[3][3] = {1/16.0, 1/8.0, 1/16.0, 1/8.0, 1/4.0, 1/8.0, 1/16.0, 1/8.0, 1/16.0},sum1 = 0, sum2 = 0, sum3 = 0, g=0, avg1, avg2, avg3;
int i, j, k, l;

int main(int argc, char** argv)
{
  int r;
  Mat img = imread(argv[1],CV_LOAD_IMAGE_COLOR);
  Mat img2(img.rows, img.cols, CV_8UC3, Scalar(255,255,255));
  for(r=0; r<20;r++)
    {
      for(i=0; i<img.rows; i++)
	{
	  for(j=0; j<img.cols; j++)
	    {
	      for(k=-1; k<=1; k++)
		{
		  for(l=-1; l<=1; l++)
		    {
		      
		      if(k+i>=0 && l+j<img.cols && k+i<img.rows && j +l>=0)
			{
			  
			  sum1+= a[k+1][l+1]*img.at<Vec3b>(i+k, j+l)[0];
			  sum2+= a[k+1][l+1]*img.at<Vec3b>(i+k, j+l)[1];
			  sum3+= a[k+1][l+1]*img.at<Vec3b>(i+k, j+l)[2];
			  // g+=a[k+1][l+1];
			}      
		    } 
		}
	      //avg1= sum1/g;  avg2= sum2/g;   avg3= sum3/g;
	      img2.at<Vec3b>(i, j)[0] =(int)sum1;
	      img2.at<Vec3b>(i, j)[1] = (int)sum2;
	      img2.at<Vec3b>(i, j)[2] = (int)sum3;
	      g=0;
	      sum1=0;
	      sum2=0;
	      sum3=0;
	      
	    }
	}
      img=img2;
    }
  imshow("blurred", img2);
  waitKey(0);

}

