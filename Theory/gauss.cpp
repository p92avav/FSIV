#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void gaussblur(Mat src, Mat dst, Mat kernel) {

    for(int i=0; i<src.rows - 0; i++) 
    {
        for(int j=0; j<src.cols - 0; j++) 
        {
            float p = 0;
            for(int k=0; k<kernel.rows; k++) 
            {
                for(int l=0; l<kernel.cols; l++) 
                {
                    if(i+k < src.rows && j+l < src.cols) 
                    {
                        p += (src.at<uchar>(i + k,j + l) * kernel.at<double>(k,l));                    
                    }
                }
            }

            if(i + kernel.rows/2 < src.rows && j + kernel.cols/2 < src.cols) 
            {
                dst.at<uchar>(i + kernel.rows/2,j + kernel.cols/2) = p / sum(kernel)[0];
            }

        }
    }
}

int main( int argc, char** argv )
{
    cv::Mat src=cv::imread(argv[1], IMREAD_GRAYSCALE);
    imshow("Input", src);

    Mat gaussMatrix;
    src.copyTo(gaussMatrix);

    Mat kernelX = getGaussianKernel(5, 1);
    Mat kernelY = getGaussianKernel(5, 1);
    Mat kernelXY = kernelX * kernelY.t();

    gaussblur(src,gaussMatrix,kernelXY);

    imshow("Output",gaussMatrix);
    cv::waitKey(0);
}