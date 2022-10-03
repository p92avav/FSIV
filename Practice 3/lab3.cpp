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

Mat originalImage, processedImage, filteredImage;
string path;

float gValue, kValue;


int main (int argc, char* const* argv)
{
    int retCode = EXIT_SUCCESS;
    system("clear");

    const String keys =
    "{help h         |             | Print this message                                            }"
    "{gamma G        |             | Value of G in the equation                                    }"
    "{K              | <none>      | Kernel size for blurring                                      }"
    "{o              |             | Path for the output image                                     }"
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

    //Aply a blurring filter to the input image

    //Obtain unsharpened image U by : U = (1+g)* OriginalImage - g*FilteredImage

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