// FSIV

#include "common_code.hpp"

using namesapce std;
using namespace cv;

void fsiv_boardPoints3d(float size, const cv::Size & patternsize, std::vector<cv::Point3f>& points3d)
{
	CV_Assert(size > 0);
	CV_Assert(patternsize.width > 0);
	CV_Assert(patternsize.height > 0);

	points3d.clear();
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

	//Calibrate camera given the corners and their 3D correspondences
	cv::calibrateCamera(points3d, cornerPoints, imageSize, cameraMatrix, distCoeffs, cv::noArray(), cv::noArray(), cv::CALIB_FIX_K3 | cv::CALIB_FIX_K4 | cv::CALIB_FIX_K5);
}

// TO DO: define all the extra functions that you might need
