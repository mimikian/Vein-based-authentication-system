#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Skeleton.h"
#include "ImgProcessor.h"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;
int main()
{
	
	// Load an image given path
	string path = "VeinsSamples/yomna1.tiff";
	//Mat src = imread("VeinsSamples/pascal.tif");
	Mat src = imread(path);
	imshow("Original", src);

	//Image processing
	ImgProcessor imgProcessor;
	imgProcessor.set_values(src);
	Mat dst = imgProcessor.run();

	// Sekelenization
	Mat skel;
	//Canny(dst, skel, 10, 350);
	Skeleton skeleton;
	skeleton.set_values(dst);
	skel = skeleton.run();
	imshow("Skeleton", skel);
	
	waitKey(0);
	return 1;
}