// FSIV

#include "common_code.hpp"
#include <opencv2/calib3d.hpp>

using namespace std;
using namespace cv;

void fsiv_boardPoints3d(float size, const cv::Size & patternsize, std::vector<cv::Point3f>& points3d)
{

	CV_Assert(size > 0);
	//Create a list of 3D points representing the position in the real world of the corners (Z=0)
	
	for (int i = 0; i < patternsize.height; i++)
	{
		for (int j = 0; j < patternsize.width; j++)
		{
			points3d.push_back(Point3f(j*size, i*size, 0));
		}
	}
}

void fsiv_calibrateCamera(const std::vector<vector<cv::Point3f> > & points3d, const vector<vector<Point2f> > & cornerPoints, const cv::Size & imageSize, cv::Mat & cameraMatrix, cv::Mat & distCoeffs)
{
	CV_Assert(points3d.size() > 0);
	CV_Assert(cornerPoints.size() > 0);

	cout<<"Number of 3D points: "<<points3d.size()<<endl;
	cout<<"Number of 2D points: "<<cornerPoints.size()<<endl;
	cout<<"Image size: "<<imageSize<<endl;
	cout<<"Camera matrix: "<<cameraMatrix<<endl;
	cout<<"Distortion coefficients: "<<distCoeffs<<endl;
	
	vector<Mat> rvecs, tvecs;
	calibrateCamera(points3d, cornerPoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs);
}

// TO DO: define all the extra functions that you might need
