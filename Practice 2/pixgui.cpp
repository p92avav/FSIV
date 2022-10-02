/*!
  Template program for the Computer Vision course.

  Author: Manuel J Marin-Jimenez, University of Cordoba

*/

#include <iostream>
#include <exception>
#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>

//#include "common_code.hpp"

using namespace std;
using namespace cv;

//TODO: Check overflow and round numbers convertTo();

const int mult_slider_max = 100;
const int add_slider_max = 255;
int mult_slider, add_slider;
double mult, addi, hasMinus;

Mat originalImage, processedImage, originalGrayscale;

string path;

uchar myAdd(uchar v, uchar k)
{
    uchar res;
    if(v + int(k) > 255)
    {
        res = 255;
    }
    else
    {
        res = v + k;
    }
    return res;
}

uchar mySub(uchar v, uchar k)
{
    uchar res;
    if(v - int(k) < 0)
    {
        res = 0;
    }
    else
    {
        res = v - k;
    }
    return res;
}

static void on_trackbar_mult(int, void*)
{
    mult = (double) mult_slider / mult_slider_max;

    for(int i = 0; i < processedImage.rows;i++)
    {
        for(int j = 0; j < processedImage.cols; j++)
        {
            Vec3b ptr = processedImage.at<Vec3b>(Point(j,i));

            ptr[0] = ptr[0] * mult;
            ptr[1] = ptr[1] * mult;
            ptr[2] = ptr[2] * mult;

            processedImage.at<Vec3b>(Point(j,i))=ptr;
        }
    }
    
    cv::imshow("Processed", processedImage);
}

static void on_trackbar_add(int, void*)
{
    addi = (double) add_slider;
    
    if((int)hasMinus % 2 == 0)
    {
        for(int i = 0; i < processedImage.rows;i++)
        {
            for(int j = 0; j < processedImage.cols; j++)
            {
                Vec3b ptr = processedImage.at<Vec3b>(Point(j,i));
                
                ptr[0] = myAdd(ptr[0], addi);
                ptr[1] = myAdd(ptr[1], addi);
                ptr[2] = myAdd(ptr[2], addi);

                processedImage.at<Vec3b>(Point(j,i))=ptr;
            }
        }
    }
    else if((int)hasMinus % 2 == 1)
    {
        for(int i = 0; i < processedImage.rows;i++)
        {
            for(int j = 0; j < processedImage.cols; j++)
            {
                Vec3b ptr = processedImage.at<Vec3b>(Point(j,i));
                
                ptr[0] = mySub(ptr[0], addi);
                ptr[1] = mySub(ptr[1], addi);
                ptr[2] = mySub(ptr[2], addi);

                processedImage.at<Vec3b>(Point(j,i))=ptr;
            }
        }
    }

    cv::imshow("Processed", processedImage);
}

static void invertImage(Mat Image)
{
    for(int i = 0; i < processedImage.rows;i++)
    {
        for(int j = 0; j < processedImage.cols; j++)
        {
            Vec3b ptr = processedImage.at<Vec3b>(Point(j,i));
            
            ptr[0] = 255 - ptr[0];
            ptr[1] = 255 - ptr[1];
            ptr[2] = 255 - ptr[2];

            processedImage.at<Vec3b>(Point(j,i))=ptr;
        }
    }
}

int main (int argc, char* const* argv)
{
    int retCode = EXIT_SUCCESS;
    system("clear");

    const String keys =
    "{help h         |             | Print this message                                            }"
    "{g              |             | Loads the original image in grayscale                         }"
    "{o              | <none>      | File where the output image will be saved. Mandatory parameter}"
    ;

    CommandLineParser parser(argc, argv, keys);
    parser.about("Creating a GUI trackbar");

    bool hasGray = false;

    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }

    if(parser.has("g"))
    {
        hasGray = true;
    }

    if(parser.has("o"))
    {
        path = parser.get<cv::String>("o");

    }
    else
    {
        parser.printMessage();
        return 0;
    }

    originalImage = imread(argv[1], IMREAD_COLOR);   

    if(hasGray == true)
    {
        for(int i = 0; i < originalImage.rows;i++)
        {
            for(int j = 0; j < originalImage.cols; j++)
            {
                Vec3b ptr = originalImage.at<Vec3b>(Point(j,i));
                float value = ((0.299*ptr[0]) + (0.587*ptr[1]) + (0.114*ptr[2]));
                ptr[0] = value;
                ptr[1] = value;
                ptr[2] = value; 
                originalImage.at<Vec3b>(Point(j,i))=ptr;
            }
        }
    }

    originalImage.copyTo(processedImage);

    // Type your code here and within 'common_code.cpp' 

    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE); // Create Window
    cv::namedWindow("Processed", cv::WINDOW_AUTOSIZE); // Create Window

    cv::createTrackbar("Mult", "Original", &mult_slider, mult_slider_max, on_trackbar_mult);
    cv::createTrackbar("Add", "Original", &add_slider, add_slider_max, on_trackbar_add);

    cv::imshow("Original", originalImage);
    cv::imshow("Processed", processedImage);

    char key = 0;
    do {
        key = cv::waitKey(0);
        if(key == 'm' || key == 'M')
        {
            hasMinus ++;
        }
        
        if(key == 's' || key == 'S')
        {
            imwrite(path, processedImage);
        }
        if(key == 'i' || key == 'I')
        {
            invertImage(processedImage);
            cv::imshow("Processed", processedImage);
        }

    } while (key != 27);

    std::cout << "End of the process!" << std::endl;
    return retCode;
}
