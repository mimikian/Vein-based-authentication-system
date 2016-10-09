#include "Skeleton.h"

void Skeleton::set_values(Mat img){
	src = img;
}

Mat Skeleton::run(){
	Mat img = src;
	Mat skel(img.size(), CV_8UC1, Scalar(0));
	Mat temp;
	Mat eroded;
	Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));
	Mat element1 = getStructuringElement(MORPH_CROSS, Size(13, 13));
	
	bool done;
	do{
		erode(img, eroded, element);
		dilate(eroded, temp, element); // temp = open(img)
		subtract(img, temp, temp);
		bitwise_or(skel, temp, skel);
		eroded.copyTo(img);
		done = (countNonZero(img) == 0);
	} while (!done);

	GaussianBlur(skel, skel, Size(0, 0), 0.8);
	return skel;
}

