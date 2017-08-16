#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace cv::fisheye;
using namespace std;

int i,j,t,p;

void displayimage(Mat image, String windowname){

    imshow(windowname, image);
}


Mat readimage(String filename)
{
    return imread(filename);
}

/*void undistortImage	(Mat image,
Mat img,
float K[3][3],
float D[4],
float Knew[3][3],
const Size & 	new_size = Size()
);*/





int main(int argc, char** argv){
    //Mat image=imread(argv[1],CV_LOAD_IMAGE_COLOR);
    //imshow("ima",image);
    cv::Mat distortMat = (cv::Mat_<double>(1, 5) << -0.300247, 0.050778, -0.004780, -0.002455, 0.000000);
    cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3) << 335.582219, 0.000000, 322.133257,
    0.000000, 332.279789, 266.496939,
    0.000000, 0.000000 ,1.000000);
    cv::Mat img = cv::imread("input.jpg", 1);
    cv::cvtColor(img, img, CV_BGR2GRAY);
    img.convertTo(img, CV_8UC1);
    cv::Mat uPhoto = img.clone();

    double k1 = distortMat.at<double>(0, 0);
    double k2 = distortMat.at<double>(0, 1);
    double p1 = distortMat.at<double>(0, 2);
    double p2 = distortMat.at<double>(0, 3);
    double k3 = distortMat.at<double>(0, 4);
    double  fx = cameraMatrix.at<double>(0, 0);
    double  cx = cameraMatrix.at<double>(0, 2);
    double  fy = cameraMatrix.at<double>(1, 1);
    double  cy = cameraMatrix.at<double>(1, 2);
    double z = 1.;

    for (int i = 0; i < img.cols; i++)
    {
      for (int j = 0; j < img.rows; j++)
      {
        /* Solved by removing this...
        double x = (double)i*fx + cx*z;
        double y = (double)j*fy + cy*z;
        double r2 = x*x + y*y;

        double dx = 2 * p1*i*j + p2*(r2 + 2 * i*i);
        double dy = p1*(r2 + 2 * j*j) + 2 * p2*i*j;
        double scale = 1. + k1*r2 + k2*r2*r2 + k3*r2*r2*r2;

        double xCorr = x*scale + dx;
        double yCorr = y*scale + dy;*/

        // ...and adding this:
        double x = (i - cx) / fx;
        double y = (j - cy) / fy;
        double r2 = x*x + y*y;

        double dx = 2 * p1*x*y + p2*(r2 + 2 * x*x);
        double dy = p1*(r2 + 2 * y*y) + 2 * p2*x*y;
        double scale = (1 + k1*r2 + k2*r2*r2 + k3*r2*r2*r2);

        double xBis = x*scale + dx;
        double yBis = y*scale + dy;

        double xCorr = xBis*fx + cx;
        double yCorr = yBis*fy + cy;

        if (xCorr >= 0 && xCorr < uPhoto.cols && yCorr >= 0 && yCorr < uPhoto.rows)
        {
            uPhoto.at<uchar>(yCorr, xCorr) = img.at<uchar>(j, i);
        }
      }
    }

    cv::imwrite("uPhotoManual.jpg", uPhoto);

    cv::Mat uPhotoAuto;
    cv::undistort(img, uPhotoAuto, cameraMatrix, distortMat);
    cv::imwrite("uPhotoAuto.jpg", uPhotoAuto);

    return 0;
}
