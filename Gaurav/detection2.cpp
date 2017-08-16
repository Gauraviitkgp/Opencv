#include <stdio.h>
#include <vector>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

Mat hsv_img;

void displayimage(Mat image, String windowname){
    imshow(windowname, image);
  }


Mat readimage(String filename){
    return imread(filename);
}

void mouseCB(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
          cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
          cout << (int)hsv_img.at<Vec3b>(y,x)[0] << " " << (int)hsv_img.at<Vec3b>(y,x)[1] << " " << (int)hsv_img.at<Vec3b>(y,x)[2] << endl;
     }
}

void FindBlobs(const Mat &binary, vector < vector<Point2i> > &blobs)
{
    blobs.clear();

    // Fill the label_image with the blobs
    // 0  - background
    // 1  - unlabelled foreground
    // 2+ - labelled foreground

    Mat label_image;
    binary.convertTo(label_image, CV_32SC1);

    int label_count = 2; // starts at 2 because 0,1 are used already

    for(int y=0; y < label_image.rows; y++) {
        int *row = (int*)label_image.ptr(y);
        for(int x=0; x < label_image.cols; x++) {
            if(row[x] != 1) {
                continue;
            }

            Rect rect;
            floodFill(label_image, Point(x,y), label_count, &rect, 0, 0, 4);

            vector <Point2i> blob;

            for(int i=rect.y; i < (rect.y+rect.height); i++) {
                int *row2 = (int*)label_image.ptr(i);
                for(int j=rect.x; j < (rect.x+rect.width); j++) {
                    if(row2[j] != label_count) {
                        continue;
                    }

                    blob.push_back(Point2i(j,i));
                    cout << "Pushing";
                }
            }

            blobs.push_back(blob);

            label_count++;
        }
    }
}


int main(int argc, char** argv){

    Mat img=imread(argv[1],CV_LOAD_IMAGE_COLOR);
    Mat grid_thr, grid_thr_l, no_grid, rb_thr, gb_thr, gb, rb, allb;

    cvtColor(img, hsv_img, CV_BGR2HSV_FULL);

    int h=167,s=18,v=0,ht=14,st=13;
    int h_g=82,s_g=101,v_g=0,ht_g=28,st_g=86;
    int h_r=255,s_r=103,v_r=0,ht_r=16,st_r=49;

    namedWindow("Sliders");
    namedWindow("MainIM");
    setMouseCallback("MainIM", mouseCB, NULL);
    createTrackbar("H","Sliders",&h,255);
    createTrackbar("S","Sliders",&s,255);
    createTrackbar("V","Sliders",&v,255);
    createTrackbar("HT","Sliders",&ht,255);
    createTrackbar("ST","Sliders",&st,255);

    createTrackbar("H_G","Sliders",&h_g,255);
    createTrackbar("S_G","Sliders",&s_g,255);
    createTrackbar("V_G","Sliders",&v_g,255);
    createTrackbar("HT_G","Sliders",&ht_g,255);
    createTrackbar("ST_G","Sliders",&st_g,255);

    createTrackbar("H_R","Sliders",&h_r,255);
    createTrackbar("S_R","Sliders",&s_r,255);
    createTrackbar("V_R","Sliders",&v_r,255);
    createTrackbar("HT_R","Sliders",&ht_r,255);
    createTrackbar("ST_R","Sliders",&st_r,255);

    imshow("MainIM",img);
    while(1){
      inRange(hsv_img,Scalar(h-ht,s-st,0), Scalar(h+ht,s+st,255),grid_thr);
      inRange(hsv_img,Scalar(h_g-ht_g,s_g-st_g,0), Scalar(h_g+ht_g,s_g+st_g,255),gb_thr);
      inRange(hsv_img,Scalar(h_r-ht_r,s_r-st_r,0), Scalar(h_r+ht_r,s_r+st_r,255),rb_thr);

      vector < vector<Point2i > > blobs;
      Mat grid_thr_s;
      //cout << grid_thr.channels() << endl;
      FindBlobs(grid_thr, blobs);
      int largest_blob_id = 0;
      int largest_blob_size = 0;
      for(int i=0; i<blobs.size(); i++){
        if(blobs[i].size() > largest_blob_size){
          largest_blob_size = blobs[i].size();
          largest_blob_id = i;
        }
      }

      //cout << largest_blob_id << " " << largest_blob_size << " " << blobs.size()  << endl;

      // grid_thr_l = Mat(grid_thr.rows, grid_thr.cols, CV_8UC1, Scalar(0));
      //
      // for(int i=0; i<blobs[largest_blob_id].size(); i++){
      //   int x = blobs[largest_blob_id][i].x;
      //   int y = blobs[largest_blob_id][i].y;
      //   grid_thr_l.at<uchar>(y,x) = 255;
      // }

      bitwise_not(grid_thr, no_grid);
      bitwise_and(no_grid, gb_thr, gb);
      bitwise_and(no_grid, rb_thr, rb);
      bitwise_or(rb, gb, allb);
      imshow("gthr", grid_thr);
      // imshow("nog", no_grid);
      // imshow("gbthr", gb_thr);
      // imshow("rbthr", rb_thr);

      imshow("rb", rb);
      imshow("gb", gb);
      imshow("allb", allb);
      waitKey(33);
    }

    return 0;
}
