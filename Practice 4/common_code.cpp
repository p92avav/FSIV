// FSIV

#include "common_code.hpp"

// Define a cv::Mat containing a cube in 3D of 1x1x1
// The cube is centered in (0.5, 0.5, 0.5)
cv::Mat fsiv_cube3d(void)
{
	cv::Mat cube(8, 3, CV_32F);
	cube.at<float>(0, 0) = 0;
	cube.at<float>(0, 1) = 0;
	cube.at<float>(0, 2) = 0;
	cube.at<float>(1, 0) = 1;
	cube.at<float>(1, 1) = 0;
	cube.at<float>(1, 2) = 0;
	cube.at<float>(2, 0) = 1;
	cube.at<float>(2, 1) = 1;
	cube.at<float>(2, 2) = 0;
	cube.at<float>(3, 0) = 0;
	cube.at<float>(3, 1) = 1;
	cube.at<float>(3, 2) = 0;
	cube.at<float>(4, 0) = 0;
	cube.at<float>(4, 1) = 0;
	cube.at<float>(4, 2) = 1;
	cube.at<float>(5, 0) = 1;
	cube.at<float>(5, 1) = 0;
	cube.at<float>(5, 2) = 1;
	cube.at<float>(6, 0) = 1;
	cube.at<float>(6, 1) = 1;
	cube.at<float>(6, 2) = 1;
	cube.at<float>(7, 0) = 0;
	cube.at<float>(7, 1) = 1;
	cube.at<float>(7, 2) = 1;
	return cube;
}

// Creates a 3D projection matrix 3x4
// The projection is a perspective projection
cv::Mat fsiv_cameraMatrix(float f, float cx, float cy)
{
	cv::Mat cam(3, 4, CV_32F);

	cam.at<float>(0, 0) = f;
	cam.at<float>(0, 1) = 0;
	cam.at<float>(0, 2) = cx;
	cam.at<float>(0, 3) = 0;
	cam.at<float>(1, 0) = 0;
	cam.at<float>(1, 1) = f;
	cam.at<float>(1, 2) = cy;
	cam.at<float>(1, 3) = 0;
	cam.at<float>(2, 0) = 0;
	cam.at<float>(2, 1) = 0;
	cam.at<float>(2, 2) = 1;
	cam.at<float>(2, 3) = 0;

	return cam;
}

// Create a rotation matrix
// The rotation is a rotation around the Z axis
cv::Mat rotationMatrixZ(float angle)
{
	cv::Mat rot(3, 3, CV_32F);

	rot.at<float>(0, 0) = cos(angle);
	rot.at<float>(0, 1) = -sin(angle);
	rot.at<float>(0, 2) = 0;
	rot.at<float>(1, 0) = sin(angle);
	rot.at<float>(1, 1) = cos(angle);
	rot.at<float>(1, 2) = 0;
	rot.at<float>(2, 0) = 0;
	rot.at<float>(2, 1) = 0;
	rot.at<float>(2, 2) = 1;
	// Can be 4x4?

	return rot;
}

// Function to project 3d points to 2d points using a projection matrix
// The projection matrix is a 3x4 matrix
// The 3d points are a Nx3 matrix
// The 2d points are a Nx2 matrix
// You may use 'mat2homog'
cv::Mat fsiv_projectPoints(cv::Mat& points3d, cv::Mat& projection)
{
	cv::Mat points2d(points3d.rows, 2, CV_32F);
	
	CV_Assert(points3d.cols == 3);	
	CV_Assert(projection.cols == 4 && projection.rows == 3);

	
	cv::Mat points3d_h = fsiv_mat2homog(points3d);
	cv::Mat points2d_h = points3d_h * projection.t();
	//Convert points2d_h from homogeneous to euclidean
	for (int i = 0; i < points2d_h.rows; i++)
	{
		points2d.at<float>(i, 0) = points2d_h.at<float>(i, 0) / points2d_h.at<float>(i, 2);
		points2d.at<float>(i, 1) = points2d_h.at<float>(i, 1) / points2d_h.at<float>(i, 2);
	}

	return points2d;
}

cv::Mat fsiv_mat2homog(cv::Mat& m)
{
	cv::Mat ch;

	//Convert to homogeneous coordinates
	if (m.cols == 1)
	{
		ch = cv::Mat::ones(m.rows + 1, 1, CV_32F);
		m.copyTo(ch(cv::Rect(0, 0, 1, m.rows)));
	}
	else if (m.rows == 1)
	{
		ch = cv::Mat::ones(1, m.cols + 1, CV_32F);
		m.copyTo(ch(cv::Rect(0, 0, m.cols, 1)));
	}
	else
	{
		ch = cv::Mat::ones(m.rows + 1, m.cols + 1, CV_32F);
		m.copyTo(ch(cv::Rect(0, 0, m.cols, m.rows)));
	}

	return ch;
}

//=================================== DRAWING FUNCTIONS =============================
// Draw a face of a 3d cube
void drawFace(cv::Mat& img, const cv::Mat& cube2d, int* idx_face, cv::Scalar& color)
{
	CV_Assert(cube2d.cols == 2);

	for (int i = 0; i < 4; i++)
	{
		std::string text = std::to_string(idx_face[i]);
		cv::Point2f p1 = cv::Point2f(cube2d.at<float>(idx_face[i], 0), cube2d.at<float>(idx_face[i], 1));
		cv::Point2f p2 = cv::Point2f(cube2d.at<float>(idx_face[(i + 1) % 4], 0), cube2d.at<float>(idx_face[(i + 1) % 4], 1));
		cv::putText(img, text, p1, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 1, 8, false);
		cv::line(img, p1, p2, color, 2);				
	}
	
}

// This function requires 'drawFace'
void fsiv_drawFullCubeOnImage(cv::Mat& img, const cv::Mat& cube2d)
{
	cv::Scalar color1(0, 255, 0);
	cv::Scalar color2(0, 0, 255);
	cv::Scalar color3(255, 0, 0);
	cv::Scalar color4(255, 255, 0);

	int idx_face1[4] = { 0,1,2,3 };
	drawFace(img, cube2d, idx_face1, color1);

	int idx_face2[4] = { 4,5,6,7 };
	drawFace(img, cube2d, idx_face2, color2);

	int idx_face3[4] = { 1, 2, 4, 7 };
	drawFace(img, cube2d, idx_face3, color3);

	int idx_face4[4] = { 0, 3, 5, 6 };
	drawFace(img, cube2d, idx_face4, color4);
}

// TO DO: define all the extra functions that you might need
