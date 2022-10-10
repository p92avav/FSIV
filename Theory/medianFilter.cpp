#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
#include <cmath>
using namespace std;
using namespace cv;

Mat image, output;
int kValue;
bool coloredImage;

void medianFilterGray(Mat &inputImage, Mat &outputImage, int kernelSize)
{
    output = Mat::zeros(image.rows, image.cols, CV_8UC1);
    
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            int median = 0, medianIndex = 0;
            int *medianArray = new int[kernelSize * kernelSize];

            for (int k = 0; k < kernelSize; k++)
            {
                for (int l = 0; l < kernelSize; l++)
                {
                    medianArray[medianIndex] = image.at<uchar>(i + k, j + l);
                    medianIndex++;
                }
            }
    
            for (int k = 0; k < kernelSize * kernelSize; k++)
            {
                for (int l = 0; l < kernelSize * kernelSize - 1; l++)
                {
                    if (medianArray[l] > medianArray[l + 1])
                    {
                        int aux = medianArray[l];
                        medianArray[l] = medianArray[l + 1];
                        medianArray[l + 1] = aux;
                    }
                }
            }

            median = medianArray[(kernelSize * kernelSize) / 2];
            output.at<uchar>(i, j) = median;
        }
    }
}


void medianFilterColor(Mat &inputImage, Mat &outputImage, int kernelSize)
{
    output = Mat::zeros(image.rows, image.cols, CV_8UC3);
    
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            int medianB=0, medianG=0, medianR=0, medianIndex=0;

            int *medianArrayB = new int[kernelSize * kernelSize];
            int *medianArrayG = new int[kernelSize * kernelSize];
            int *medianArrayR = new int[kernelSize * kernelSize];
            

            for (int k = 0; k < kernelSize; k++)
            {
                for (int l = 0; l < kernelSize; l++)
                {
                    medianArrayB[medianIndex] = image.at<Vec3b>(i + k, j + l)[0];
                    medianArrayG[medianIndex] = image.at<Vec3b>(i + k, j + l)[1];
                    medianArrayR[medianIndex] = image.at<Vec3b>(i + k, j + l)[2];                 
                    medianIndex++;
                }
            }
    
            for (int k = 0; k < kernelSize * kernelSize; k++)
            {
                for (int l = 0; l < kernelSize * kernelSize - 1; l++)
                {
                    if (medianArrayB[l] > medianArrayB[l + 1])
                    {
                        int aux = medianArrayB[l];
                        medianArrayB[l] = medianArrayB[l + 1];
                        medianArrayB[l + 1] = aux;
                    }
                    if (medianArrayG[l] > medianArrayG[l + 1])
                    {
                        int aux = medianArrayG[l];
                        medianArrayG[l] = medianArrayG[l + 1];
                        medianArrayG[l + 1] = aux;
                    }
                    if (medianArrayR[l] > medianArrayR[l + 1])
                    {
                        int aux = medianArrayR[l];
                        medianArrayR[l] = medianArrayR[l + 1];
                        medianArrayR[l + 1] = aux;
                    }
                }
            }

            
            medianB = medianArrayB[(kernelSize * kernelSize) / 2];
            medianG = medianArrayG[(kernelSize * kernelSize) / 2];
            medianR = medianArrayR[(kernelSize * kernelSize) / 2];
            
            output.at<Vec3b>(i, j)[0] = medianB;
            output.at<Vec3b>(i, j)[1] = medianG;
            output.at<Vec3b>(i, j)[2] = medianR;
            
        }
    }
}



int main(int argc,char **argv)
{
    const String keys =
        "{help h         |   | print this message      }"
        "{K              |   | Kernel size             }"
        "{color c        |   | Colored Image           }"
        ;

    CommandLineParser parser(argc, argv, keys);
    parser.about("Median Filter");

    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }

    if(parser.has("K"))
    {
        kValue = parser.get<int>("K");
    }
    else
    {
        kValue = 3;
    }
    
    if(parser.has("color"))
    {
        coloredImage = true;
    }
    else
    {
        coloredImage = false;
    }


    if(coloredImage == true)
    {
        image=cv::imread(argv[1], cv::IMREAD_COLOR);
        medianFilterColor(image, output, kValue);
    }
    else
    {
        image=cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
        medianFilterGray(image, output, kValue);
    }

    cv::namedWindow("Input");
    cv::imshow("Input",image);

    cv::namedWindow("Output");  
    cv::imshow("Output",output);
    
    char key = 0;
    do 
    {
        key = cv::waitKey(0);
        if(key == 's' || key == 'S')
        {
            imwrite("output.jpg", output);
        }
    } while (key != 27);              
}

