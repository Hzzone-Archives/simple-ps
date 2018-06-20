#ifndef SIMPLE_MODE_TRANS_H
#define SIMPLE_MODE_TRANS_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
using namespace cv;

Mat single_threshold(Mat mat, double threshold);
Mat dithering(Mat I, Mat D);
Mat ordered_dithering(Mat I, Mat D);
Mat gray(Mat I);


#endif // SIMPLE_MODE_TRANS_H
