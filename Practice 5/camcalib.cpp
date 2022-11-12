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

#include "common_code.hpp"

using namespace std;
using namespace cv;

const String keys =
"{help h usage ? |      | print this message   }"
"{list           | images.txt | path to txt with filenames }"
"{size		   	 | 		| size of the squares in mm }"
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

	float sqsize = 100;
	String outname = parser.get<String>("out");
	
	String listtxt = parser.get<String>("list");
	
	std::vector<String> lfiles;
	
	int squareSize = parser.get<int>("size");

	cv::Size imageSize;

	// Read the list of files
	std::ifstream list(listtxt);
	if (!list.is_open())
	{
		std::cerr << "Error opening file " << listtxt << std::endl;
		return -1;
	}

	String filename;
	while (list >> filename)
	{
		lfiles.push_back(filename);
	}

	cout<<endl<<"TEST VER SI LEE BIEN LOS ARCHIVOS Y LOS GUARDA EN EL VECTOR"<<endl;
	for(int i=0;i<lfiles.size();i++){
		cout<<lfiles[i]<<endl;
	}

	try {

		// Create a window to display the images
		cv::namedWindow("ImagePattern");
		vector<vector<Point2f> > imagePoints;
		cv::Size patternsize = cv::Size(5, 4);

		for (int fix = 0; fix < lfiles.size(); fix++)
		{

			// TODO: find corners in current image
			cv::findChessboardCorners(cv::imread(lfiles[fix]), patternsize, imagePoints[fix], CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

			// TODO: add corners to the vector of image corners

		}
		
		// TODO
		// CALIBRATION GOES HERE
		
		// TODO: prepare 3D points
		
		// TODO: run camera calibration

	}catch(std::exception &ex)
	{
	  cout<<ex.what()<<endl;
	}

	return 0;
}
 
