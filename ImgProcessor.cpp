#include "ImgProcessor.h"
#include <iostream>


using namespace std;
void ImgProcessor::set_values(Mat img){
	src = img;
}

Mat ImgProcessor::run(){
	Mat dst;
	medianBlur(src, dst, 5);

	//Convert to Gray scale image
	cvtColor(dst, dst, COLOR_RGB2GRAY);
	//median filter
	medianBlur(dst, dst, 5);

	//Gaussian filter
	GaussianBlur(dst, dst, Size(0, 0), 0.8);
	//imshow("gaussian filter", dst);

	//Normlization
	Scalar avg, sdv;
	meanStdDev(dst, avg, sdv);
	sdv.val[0] = sqrt(dst.cols*dst.rows*sdv.val[0] * sdv.val[0]);
	double variance = std::sqrt(sdv.val[0]);
	double mean = avg[0];
	unsigned char *input = (unsigned char*)(dst.data);
	double low = mean - variance;
	double high = mean+ variance;
	medianBlur(dst, dst, 11);
	normalize(dst, dst, 64, 128, NORM_MINMAX);
	//imshow("Normalization", dst);
	
	//Thresholding

	// Binary threshold
	//threshold(dst, dst, 100, 255, THRESH_BINARY);
	
	// Adaptive threshold
	adaptiveThreshold(dst, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 169, 0);
	
	//Median Filter Again to remove isloated vertices
	medianBlur(dst, dst, 13);
	GaussianBlur(dst, dst, Size(0, 0), 0.8);

	return dst;
}