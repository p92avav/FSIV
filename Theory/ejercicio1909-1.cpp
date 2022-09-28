#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
using namespace std;
using namespace cv;
cv::Mat image;

int main(int argc,char **argv){

    const String keys =
        "{help h         |   | print this message   }"
        "{@image1        |   | image1 for compare   }"
        "{T              |   | Thresholding         }"
        "{S1             |   | S1                   }"
        "{S2             |   | S2                   }"
        ;

    

    try{

        CommandLineParser parser(argc, argv, keys);
        parser.about("Prueba");

        int T = parser.get<int>("T");
        int S1 = parser.get<int>("S1");
        int S2 = parser.get<int>("S2");

        if (parser.has("help"))
        {
            parser.printMessage();
            return 0;
        }

        String img = parser.get<String>(0);
        
        cv::Mat image=cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
        if( image.rows==0) {cerr<<"Error reading image"<<endl;return 0;}

                    
            if(parser.has("T"))
            {
                for(int i=0; i<image.rows; i++)
                {
                    for(int j=0; j<image.cols; j++) 
                    {
                        if(image.at<uchar>(i,j) > T)
                        {
                            image.at<uchar>(i,j) = 0;
                        }
                        else
                        {
                            image.at<uchar>(i,j) = 255;
                        }
                    }
                }
            }
            else if(parser.has("S1") && parser.has("S2"))
            {
                for(int i = 0; i < image.rows; i++)
                {
                    for(int j = 0; j < image.cols; j++)
                    {
                        int pixelValue = (int)image.at<uchar>(i,j);
                        
                        if( pixelValue < S1)
                        {
                            image.at<uchar>(i,j) = pixelValue + 5;
                        }
                        else if(S1 < pixelValue && pixelVaue < S2)
                        {
                            image.at<uchar>(i,j) = ((log(pixelValue + 1)/log(256)) * 255);
                        }
                        else if(S2 > pixelValue)
                        {
                            image.at<uchar>(i,j) = pixelValue/2;
                        }
                    }
                }
            }               
        }

        cv::namedWindow("image");
        cv::imshow("image",image);
        cv::waitKey(0);
    }

    catch(std::exception &ex)
    {
    cout<<ex.what()<<endl;
    }
}
