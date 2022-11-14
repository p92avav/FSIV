/***********************************
 * Autor: Manuel J Marin-Jimenez
 * Universidad de Córdoba (Spain)
 * Grado en Ing Informatica
 * Asignatura: FSIV
 * 
 * Info:
 * Shows how to calibrate a camera
 *  
 * ******************************************/

#include <opencv2/core/core.hpp> 
//#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <string>
#include <fstream>

#include "common_code.hpp"

using namespace std;
using namespace cv;

const String keys =
"{help h usage ? |      | print this message   }"
"{list           | images.txt | path to txt with filenames }"
"{size           | 		| size of the square in the chessboard }"
"{out            | intrinsics.yml | output name }"
; 


// ===================================================================
// =============================== THE MAIN ==========================
// ===================================================================

int main(int argc,char **argv)
{
	CommandLineParser parser(argc, argv, keys);
	parser.about("Camera calibration");

	if (parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}

	float sqsize = parser.get<float>("size");
	String outname = parser.get<String>("out");
	
	String listtxt = parser.get<String>("list");
	
	std::vector<String> lfiles;
	
	cv::Size imageSize;

	ifstream list(listtxt);
	if (!list.is_open())
	{
		cout << "Error opening file " << listtxt << endl;
		return -1;
	}

	String filename;
	while (getline(list, filename))
	{
		lfiles.push_back(filename);
	}

	list.close();
	try {

		// Create a window to display the images
		cv::namedWindow("ImagePattern");
		vector<vector<Point2f> > imagePoints;
		cv::Size patternsize = cv::Size(5, 4);

		imagePoints.resize(lfiles.size());

		for (int fix = 0; fix < lfiles.size(); fix++)
		{
			cv::Mat readImage = cv::imread(lfiles[fix], cv::IMREAD_GRAYSCALE);
			cv::imshow("ImagePattern", readImage);
			cv::waitKey(100);
			Mat img = readImage.clone();
			// TODO: find corners in current image
			cv::findChessboardCorners(img, patternsize, imagePoints[fix], 
			CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);

			// TODO: add corners to the vector of image corners
			imagePoints.push_back(imagePoints[fix]);

			//Drawn corners
			cv::drawChessboardCorners(img, patternsize, imagePoints[fix], true);
			cv::imshow("ImagePattern", img);
			cv::waitKey(100);
		}

		// TODO
		// CALIBRATION GOES HERE

		// TODO: prepare 3D points
		vector<Point3f> points3d;
		fsiv_boardPoints3d(sqsize, patternsize, points3d);

		// TODO: run camera calibration
		Mat cameraMatrix, distCoeffs;
		//replicate points3d into a vector of vectors
		vector<vector<Point3f>> points3d2;
		for (int i = 0; i < imagePoints.size(); i++)
		{
			points3d2.push_back(points3d);
		}

		imageSize = cv::Size(640, 480);

		fsiv_calibrateCamera(points3d2, imagePoints, imageSize, cameraMatrix, distCoeffs);

		//Wirte changes into a file, including size
		FileStorage fs(outname, FileStorage::WRITE);
		fs << "image_width" << imageSize.width;
		fs << "image_height" << imageSize.height;
		fs << "camera_matrix" << cameraMatrix;
		fs << "distortion_coefficients" << distCoeffs;
		fs.release();

	}catch(std::exception &ex)
	{
	  cout<<ex.what()<<endl;
	}

	return 0;
}