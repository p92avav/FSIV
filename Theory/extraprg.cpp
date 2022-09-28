
#include <opencv2/core/core.hpp> //core routines
#include <opencv2/highgui/highgui.hpp>//imread,imshow,namedWindow,waitKey
#include <iostream>
using namespace std;
using namespace cv;
cv::Mat image;


int main(int argc,char **argv)
{
  try{
  if(argc!=2) {cerr<<"Usage:image"<<endl;return 0;} 
    //loads the image from file
    cv::Mat image=cv::imread(argv[1]);
     if( image.rows==0) {cerr<<"Error reading image"<<endl;return 0;}
     //creates a window
     cv::namedWindow("myimage");
     //displays the image in the window
     cv::imshow("myimage",image);
    char c=0;
    Vec3b x;
    while(c!=27)
    {  //waits until ESC pressed
    c=cv::waitKey(0);
      if(c==100)
      {
      for(int i=0; i<image.rows; i++)
      {
        for(int j=0; j<image.cols; j++) 
          {
            Vec3b pixel = image.at<Vec3b>(i, j);

            cout<<"Pixel ("<<i<<", "<<j<<") had the RGB value : "<< pixel <<". " <<endl; 

            float value = 1.2;
            Vec3b pixel2 = image.at<Vec3b>(i,j) = pixel/value;

            cout<<"Pixel ("<<i<<", "<<j<<") has the new RGB value : "<< pixel2 <<". " <<endl;

            uchar *ptr=image.ptr<uchar>(j)+3*i;

            ptr[0]=pixel2[0];
            ptr[1]=pixel2[1];
            ptr[2]=pixel2[2];
            cv::imshow("image",image);
            
          }
        }
        cv::imshow("myimage",image);
      }

      else if(c==105)
      {
        for(int i=0; i<image.rows; i++)
      {
        for(int j=0; j<image.cols; j++) 
          {
            Vec3b pixel = image.at<Vec3b>(i, j);

            cout<<"Pixel ("<<i<<", "<<j<<") had the RGB value : "<< pixel <<". " <<endl; 

            float value = 1.2;
            Vec3b pixel2 = image.at<Vec3b>(i,j) = pixel*value;

            cout<<"Pixel ("<<i<<", "<<j<<") has the new RGB value : "<< pixel2 <<". " <<endl;

            uchar *ptr=image.ptr<uchar>(j)+3*i;

            ptr[0]=pixel2[0];
            ptr[1]=pixel2[1];
            ptr[2]=pixel2[2];
            cv::imshow("image",image);
            
          }
        }
        cv::imshow("myimage",image);
      }
    }
    cv::destroyAllWindows();
    }
    catch(std::exception &ex)
    {
      cout<<ex.what()<<endl;
    }
}
 
