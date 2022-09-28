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
#include <opencv2/calib3d/calib3d.hpp>

//#include "common_code.hpp"

using namespace std;
using namespace cv;

Mat imageColor, imageGray, mask, auxMask;
int counter = 0;
int inv = 0;
vector<Point> mouseClicks;

void on_click (int event, int x, int y, int flags, void* param)
{
  if(event == EVENT_LBUTTONDOWN )
  {
    mouseClicks.push_back(Point(x,y));
    counter ++;
  }

  else if(counter>1) // We only need two points
  {
    // Store the two corners of the rectangle
    Point point1(mouseClicks[0].x, mouseClicks[0].y);
    Point point2(mouseClicks[1].x, mouseClicks[1].y);

    rectangle(mask, point1, point2, Scalar(255,255,255), -1, 8, 0); // Create a rectangular mask
    bitwise_not(mask, auxMask); // The opposite of the mask, used for the grayscale image
    if(inv == 0)
    {
      bitwise_and(mask, imageColor, imageColor); // Use the mask in the color image
      bitwise_and(auxMask, imageGray, imageGray); // Use the mask in the grayscale image
      bitwise_or(imageColor, imageGray, imageColor); // Combine both images
    }  

    if(inv == 1)
    {
      bitwise_not(imageColor, imageColor); // Invert the color of the image
      bitwise_and(mask, imageColor, imageColor); // Use the mask in the color image
      bitwise_and(auxMask, imageGray, imageGray); // Use the mask in the grayscale image
      bitwise_or(imageColor, imageGray, imageColor); // Combine both images
    }

    imshow("Input", imageColor); // Show the output image
    
  }
}

int main (int argc, char* const* argv)
{

    const String keys =
    "{help h         |   | print this message              }"
    "{I              |   | Invert the colors of the mask   }"
    ;

    int retCode = EXIT_SUCCESS;
    // Type your code here and within 'common_code.cpp' 
    system("clear");
    try
    {
      CommandLineParser parser(argc, argv, keys);
      parser.about("Creating a rectangular mask");

      if(parser.has("I"))
      { // Check condition for the callback function
        inv++;
      }

      if (parser.has("help"))
      {
        parser.printMessage();
        return 0;
      }

      imageColor = imread(argv[1], IMREAD_COLOR);
      imageColor.copyTo(imageGray);

      //Converts the color image into a grayscale copy
      for(int i = 0; i < imageGray.rows; i++)
      {
        for(int j = 0; j < imageGray.cols; j++)
        {
          Vec3b ptr = imageGray.at<Vec3b>(Point(j,i));
          float value = ((0.299*ptr[0]) + (0.587*ptr[1]) + (0.114*ptr[2]));
          ptr[0] = value;
          ptr[1] = value;
          ptr[2] = value; 
          imageGray.at<Vec3b>(Point(j,i))=ptr;
        }
      }


      imshow("Input", imageColor);  
  
      mask = Mat::zeros(imageColor.size(), imageColor.type());

      setMouseCallback("Input", on_click);
      waitKey(0);

    }

    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      retCode = EXIT_FAILURE;
    }
  
    std::cout << "End of the process!" << std::endl;
    return retCode;
}
