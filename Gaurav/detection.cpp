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




int main(int argc, char** argv){
       
    Mat image=imread(argv[1],CV_LOAD_IMAGE_COLOR);
    imshow("ima",image);
    waitKey(0);
    return 0;
}

