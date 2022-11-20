#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
#include <cmath>
#include <opencv2/imgproc/imgproc.hpp>//canny

using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
    //Read the input video file
    VideoCapture cap(argv[1]);
    if(!cap.isOpened())
    {
        cout<<"Error opening video stream or file"<<endl;
        return -1;
    }

    //Create a window to display the video
    namedWindow("Video",WINDOW_AUTOSIZE);

    //Create a window to display the edges
    namedWindow("Edges",WINDOW_AUTOSIZE);

    //Create a black background
   

    //Create a matrix to store the video frame
    Mat frame;

    //Read the video frame by frame
    while(1)
    {
        Mat blackBackground(480,640,CV_8UC3,Scalar(0,0,0));
        Mat edges;
        //Read the video frame
        cap>>frame;

        //If the frame is empty, break immediately
        if(frame.empty())
            break;

        //Convert the frame to gray color
        cvtColor(frame,frame,COLOR_BGR2GRAY);

        //Apply the Canny edge detector
        Canny(frame,edges,50,150,3);

        //Draw the edges on the black background
        //edges.setTo(Scalar(0,255,0));
        
        frame.copyTo(blackBackground,edges);


        imshow("Video",frame);
        imshow("Edges",edges);

        waitKey(30);
    }

    //Close the video file
    cap.release();

    //Close all the windows
    destroyAllWindows();             
}