#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
using namespace std;
using namespace cv;
cv::Mat image;

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




int main(int argc,char **argv){

    const String keys =
        "{help h         |   | print this message   }"
        "{@image1        |   | image1 for compare   }"
        "{R              |   | Channel Red          }"
        "{G              |   | Channel Green        }"
        "{B              |   | Channel Blue         }"
        ;

    

    try{

        CommandLineParser parser(argc, argv, keys);
        parser.about("Prueba");

        int N = parser.get<int>("N");

        if (parser.has("help"))
        {
            parser.printMessage();
            return 0;
        }

        String img = parser.get<String>(0);
        
        cv::Mat image=cv::imread(argv[1]);
        if( image.rows==0) {cerr<<"Error reading image"<<endl;return 0;}

            for(int i=0; i<image.rows; i++)
            {
                for(int j=0; j<image.cols; j++) 
                {
                    uchar *ptr=image.ptr<uchar>(j)+3*i;
                    
                    if(parser.has("R"))
                    {
                        ptr[0]= 255-ptr[0];
                    }
                    if(parser.has("G"))
                    {
                        ptr[1]= 255-ptr[1];
                    }
                    if(parser.has("B"))
                    {
                        ptr[2]= 255-ptr[2];
                    }
                    ptr[1]= myAdd(ptr[1], N);
                    ptr[2]= myAdd(ptr[2], N);
                    
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
