#include "mode_trans.h"
#include "file_process.h"

Mat single_threshold(Mat mat, double threshold)
{

//    printf("hello");
    printf("%d %d\n", mat.cols, mat.rows);
    for (int i=0; i<mat.rows; i++)
        {
            for (int j=0; j<mat.cols; j++)
            {
                if (mat.at<uchar>(i, j) > threshold)
                {
                    mat.at<uchar>(i, j) = 255;
                }
                else {
                    mat.at<uchar>(i, j) = 0;
                }

            }
        }
    return mat;
}

Mat dithering(Mat I, Mat D)
{
    int height = I.rows, width = I.cols, n = D.rows;
    Mat O(height*n, width*n, CV_8U, cv::Scalar::all(0));
    printf("%d %d\n", O.rows, O.cols);
    double T = 256.0/(n*n+1);
    for (int x=0; x<height; x++)
    {
        for(int y=0; y<width; y++)
        {
            I.at<uchar>(x, y) = (uchar)(I.at<uchar>(x, y)/T); //I : input gray image,
        }
    }
    for (int x=0; x<height; x++)
    {
        for (int y=0; y<width; y++)
        {
        int i = x*n;
        int j = y*n;
        for (int ii=0; ii<n; ii++)
        {
            for(int jj=0; jj<n;jj++)
            {

                if((I.at<uchar>(x, y)-D.at<uchar>(ii, jj))>0){
                    O.at<uchar>(i+ii, j+jj) = 255;
                }
                else {
                    O.at<uchar>(i+ii, j+jj) = 0;
                }
            }
        }

        }
    }

    return O;
}

Mat ordered_dithering(Mat I, Mat D)
{
    int height = I.rows, width = I.cols, n = D.rows;
    Mat O(height, width, CV_8U, cv::Scalar::all(0));
    printf("%d %d\n", O.rows, O.cols);
    double T = 256.0/(n*n+1);
    for (int x=0; x<height; x++)
    {
        for(int y=0; y<width; y++)
        {
            I.at<uchar>(x, y) = (uchar)(I.at<uchar>(x, y)/T); //I : input gray image,
        }
    }
    for (int x=0; x<height; x++)
    {
        int i = x%n;
        for (int y=0; y<width; y++)
        {
            int j = y%n;
            if (I.at<uchar>(x, y)>D.at<uchar>(i, j))
                O.at<uchar>(x, y) = 255;
            else
                O.at<uchar>(x, y) = 0;
        }
    }

    return O;
}

Mat gray(Mat I)
{
    int height = I.rows, width = I.cols;
    Mat O(height, width, CV_8U, cv::Scalar::all(0));
    Mat channels[3];
    split(I, channels);

    for (int i=0; i<height; i++)
        for (int j=0; j<width; j++)
        {
            O.at<uchar>(i, j) = (uchar)((channels[0].at<uchar>(i, j)+channels[1].at<uchar>(i, j)+channels[2].at<uchar>(i, j))/3);
        }

    return O;
//    return I;
}
