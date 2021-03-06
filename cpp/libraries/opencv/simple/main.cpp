#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>

#define ESCAPE 1048603

using namespace std;

int main() {
  int c = 0;

  CvCapture* capture = cvCaptureFromCAM(0);

  if (!cvQueryFrame(capture)) {
    cout << "Video capture failed, please check the camera." << endl;
  } else {
    cout << "Video camera capture status: OK" << endl;
  }

  CvSize size = cvGetSize(cvQueryFrame(capture));

  IplImage* src = cvCreateImage(size, 8, 3 );
  IplImage* hsv_image = cvCreateImage(size, 8, 3);
  IplImage* hsv_mask = cvCreateImage(size, 8, 1);
  CvScalar  hsv_min = cvScalar(0, 30, 80, 0);
  CvScalar  hsv_max = cvScalar(20, 150, 255, 0);

  while(c != ESCAPE) {
    src = cvQueryFrame(capture);
    cvNamedWindow("src", 1);
    cvShowImage("src", src);

    cvCvtColor(src, hsv_image, CV_BGR2HSV);
    cvNamedWindow("hsv-img", 1);
    cvShowImage("hsv-img", hsv_image);

    cvInRangeS(hsv_image, hsv_min, hsv_max, hsv_mask);
    cvNamedWindow("hsv-msk", 1);
    cvShowImage("hsv-msk", hsv_mask);

    hsv_mask->origin = 1; 
    c = cvWaitKey(10);
  }

  cvReleaseCapture(&capture);
  cvDestroyAllWindows();
}