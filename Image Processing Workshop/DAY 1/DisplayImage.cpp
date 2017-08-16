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


void createimage(){
    Mat temp(640, 640, CV_8UC3, 255);
    
    for(p=0; p<640; p+=160){
    
    
    
    for(i=p; i<(p+80); i++){
        for(t=0; t<640; t+=160){
        
            for(j=t; j<(t+80); j++){
            
                temp.at<Vec3b>(i,j)[2] = 0;
                temp.at<Vec3b>(i,j)[1] = 0;
                temp.at<Vec3b>(i,j)[0] = 0;
           }
            for(j=(t+80); j<(t+160); j++){
                
                temp.at<Vec3b>(i,j)[2] = 255;
                temp.at<Vec3b>(i,j)[1] = 255;
                temp.at<Vec3b>(i,j)[0] = 255;
            }

        }
        
        
    }
     
        for(i=(p+80); i<(p+160); i++){
       for(t=0; t<640; t+=160){
                
                for(j=t; j<(t+80); j++){
                    
                    temp.at<Vec3b>(i,j)[2] = 255;
                    temp.at<Vec3b>(i,j)[1] = 255;
                    temp.at<Vec3b>(i,j)[0] = 255;
                }
                for(j=(t+80); j<(t+160); j++){
                    
                    temp.at<Vec3b>(i,j)[2] = 0;
                    temp.at<Vec3b>(i,j)[1] = 0;
                    temp.at<Vec3b>(i,j)[0] = 0;
                }
                
            }
            
            
        } }

    displayimage(temp, "random");



}




int main(){
    createimage();
    waitKey(0);
    return 0;
}


