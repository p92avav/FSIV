/***********************************
 * Autor: Manuel J Marin-Jimenez
 * Universidad de Córdoba (Spain)
 * Grado en Ing Informatica
 * Asignatura: FSIV
 * 
 * Info:
 * Shows how to project 3D points
 * 
 * 
 * ******************************************/

#include <opencv2/core/core.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

#include "common_code.hpp"

using namespace std;
using namespace cv;

const String keys =
"{help h usage ? |      | print this message   }"
"{out            | output.jpg | output name }"
; 

#define FSIV_CX 320
#define FSIV_CY 240

#define FSIV_IMROWS 480
#define FSIV_IMCOLS 640

// Create an image to display the projected cube
cv::Mat img(FSIV_IMROWS, FSIV_IMCOLS, CV_8UC3,cv::Scalar(0,0,0));
cv::Mat cube2d;

// TODO: Create the global variables to store the trackbar values
// ...
String path;
const int focal_slider_max = 200;
const int cx_slider_max = 640;
const int cy_slider_max = 480;
const int angle_slider_max = 360;
int focal_slider, cx_slider = 320, cy_slider = 240, angle_slider;

/**
  * @brief Compute the 2D points given the current parameters
*/
void fsiv_computeCube2d(cv::Mat & cube2d, float lfocal, float rangle)
{
	// Create a 3D cube
	cv::Mat cube = fsiv_cube3d();
	
	// TODO: create the rotation matrix and apply it to the cube
	// Use the following expression: cube_rot <-- (cube * Rot) - 0.5; // The -0.5 helps to vizualize the cube
	// ...
	
	cv::Mat Rot = rotationMatrixZ(rangle);
	cv::Mat cube_rot = (cube * Rot) - 0.5;

	// Create a camera matrix
	cv::Mat cam = fsiv_cameraMatrix(lfocal, cx_slider, cy_slider);

	// Project the cube
	cube2d = fsiv_projectPoints(cube_rot, cam);
}

void fsiv_recomputeCube2d(cv::Mat & cube2d, float lfocal, float rangle)
{
	fsiv_computeCube2d(cube2d, lfocal, rangle);

	// TODO: Clean the window --> set img matrix to all black
	// ...
	
	img = cv::Mat(FSIV_IMROWS, FSIV_IMCOLS, CV_8UC3,cv::Scalar(0,0,0));
	
	// Update the image
	fsiv_drawFullCubeOnImage(img, cube2d);
}

// -------------- Event handlers for the trackbars ----------------

void on_trackbar_focal(int, void*)
{
	// TODO: get the new focal length
	// ...

	// Update the image
	Mat cube2d;
	fsiv_recomputeCube2d(cube2d, focal_slider, angle_slider);

	cv::imshow("Cube", img);
}


// ===================================================================
// =============================== THE MAIN ==========================
// ===================================================================

int main(int argc,char **argv)
{
	CommandLineParser parser(argc, argv, keys);
	parser.about("Camera projection simple");

	system("clear");

	if (parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}

	if(parser.has("out"))
	{
		path = parser.get<String>("out");
	}

	try {

		// Create a window to display the projected cube
		cv::namedWindow("Cube");

		// TODO: create trackbars
		// ...

		cv::createTrackbar("Focal", "Cube", &focal_slider, focal_slider_max, on_trackbar_focal);
		cv::createTrackbar("Angle", "Cube", &angle_slider, angle_slider_max, on_trackbar_focal);
		cv::createTrackbar("CX", "Cube", &cx_slider, cx_slider_max, on_trackbar_focal);
		cv::createTrackbar("CY", "Cube", &cy_slider, cy_slider_max, on_trackbar_focal);

		cv::Mat cube2d;

		fsiv_computeCube2d(cube2d, 200, 0);
		fsiv_drawFullCubeOnImage(img, cube2d);
		// Display the projected cube
		cv::imshow("Cube", img);	

		// TODO Control keyboard to save current image into file
		// ...
		char key = 0;
		do
		{
			key = cv::waitKey(0);

			if (key == 's' || key == 'S')
			{
				cv::imwrite(path, img);
			}
		}while(key != 27);

	}catch(std::exception &ex)
	{
	  cout<<ex.what()<<endl;
	}

	return 0;
}
 
