#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
using namespace std;
using namespace cv;

Mat image, output;

void convolution(const Mat & src, int n)
{
    Mat dst(src.rows,src.cols,src.type());
    Mat kernel(n,n,CV_32F);

    for(int i = 0; i<n; i++){
		  for(int j = 0; j<n; j++){
			kernel.at<float>(i,j) = 3;
      }
    }

    src.copyTo(dst);
    float sum;

    for(int y=1;y<src.rows-1;y++)
    {
      for(int x=1;x<src.cols-1;x++)
      {
        sum=0.0;
        for(int k=-1;k<=1;k++)
        {
          for(int j=-1;j<=1;j++)
          {
            sum=sum+kernel.at<uchar>()*src.at<uchar>(y-j,x-k);
          }
        }
        dst.at<uchar>(y,x)=sum;
      }
    }

    imshow("Output",dst);
}

int main(int argc,char **argv)
{

    cv::Mat image=cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
              
    cv::namedWindow("Input");
    cv::imshow("Input",image);

    convolution(image,3);

    cv::waitKey(0);              
}