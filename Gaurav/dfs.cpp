#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

int c=1;

void dbs(int x, int y, Mat img, Mat img1)
{
  
  img1.at<uchar>(x,y) = 255/c;
  
  for(int p=-1; p<=1; p++)
    {
      for(int q=-1; q<=1; q++)
	{
	  if(p+x>=0 && q+y<img.cols && p+x<img.rows && y +q>=0){
	    if(img.at<uchar>(x+p,y+q)!=255 && img1.at<uchar>(x+p,y+q)==0)
	      {
		dbs(x+p,y+q,img,img1);
	      }
	  }
	}   
    }
}




int main(int argc, char** argv)
{
  Mat img=imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  Mat img1(img.rows, img.cols, CV_8UC1,Scalar(0));
  for(int i=0; i<img.rows; i++)
    {
      for(int j=0; j<img.cols; j++)
	{
	  if(img.at<uchar>(i,j)!=255 && img1.at<uchar>(i,j)==0)
	    {
	      dbs(i,j,img,img1);
	      c++;
	    }
	  
        }
    }
  imshow("m", img1);
  waitKey(0);
  
}
