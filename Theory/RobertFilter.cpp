#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
#include <cmath>
using namespace std;
using namespace cv;

Mat image, output;

Mat robertFilter(Mat image)
{
    output = Mat::zeros(image.rows, image.cols, CV_8UC1);
    
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            int gx = image.at<uchar>(i, j) - image.at<uchar>(i + 1, j + 1);
            int gy = image.at<uchar>(i + 1, j) - image.at<uchar>(i, j + 1);
            
            int g = sqrt(gx * gx + gy * gy);
            
            output.at<uchar>(i, j) = g;
        }
    }
    
    return output;
}



int main(int argc,char **argv)
{

    image=cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
              
    cv::namedWindow("Input");
    cv::imshow("Input",image);
    Mat output = robertFilter(image);

    cv::namedWindow("Output");  
    cv::imshow("Output",output);
    cv::waitKey(0);              
}

