#include <iostream>
#include <exception>
#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat originalImage, processedImage, filteredImage;
string path;
float gValue, kValue;
const double gSliderMax = 5;
const int kSliderMax = 100;
int gSlider, kSlider;

void blurr(Mat &image, int size) 
{
    Mat kernel = Mat::ones(size, size, CV_32F) / (float)(size * size);
    filter2D(image, image, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
}

void unsharp(Mat &inputImg, Mat &filteredImg, Mat &outputImg, float gValue) 
{
    inputImg.convertTo(inputImg, CV_32FC3);
    outputImg.convertTo(outputImg, CV_32FC3);
    filteredImg.convertTo(filteredImg, CV_32FC3);
    outputImg = (1 + gValue) * inputImg - gValue * filteredImg;
    outputImg.convertTo(outputImg, CV_8U);
}

int main (int argc, char* const* argv)
{
    int retCode = EXIT_SUCCESS;
    system("clear");

    const String keys =
    "{help h         |             | Print this message                                            }"
    "{gamma G        |             | Value of G in the equation                                    }"
    "{K              |             | Kernel size for blurring                                      }"
    "{o              |             | Path for the output image                                     }";
    ;

    CommandLineParser parser(argc, argv, keys);
    parser.about("Creating a GUI trackbar");

    bool hasGray = false;

    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }
    if(parser.has("o"))
    {
        path = parser.get<cv::String>("o");
    }

    if(parser.has("gamma") && parser.has("K"))
    {
        gValue = parser.get<int>("gamma");
        kValue = parser.get<int>("K");
    }

    else
    {
        parser.printMessage();
        return 0;
    }

    originalImage = imread(argv[1], IMREAD_COLOR);  
    originalImage.copyTo(filteredImage);

    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::imshow("Original", originalImage);

    blurr(filteredImage, kValue);
    unsharp(originalImage, filteredImage, processedImage, gValue);
    cv::namedWindow("Unsharpened image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Unsharpened image", processedImage);
    
    char key = 0;
    do {
        key = cv::waitKey(0);
        
        if(key == 's' || key == 'S')
        {
            imwrite(path, processedImage);
        }
    } while (key != 27);

    std::cout << "End of the process!" << std::endl;
    return retCode;
}