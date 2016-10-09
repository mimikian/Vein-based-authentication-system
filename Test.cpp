#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/shape/shape.hpp"
#include <iostream>

#include <ctime>        // std::time

using namespace cv;
using namespace std;
/*
* shape_context.cpp -- Shape context demo for shape matching
*/

#include "opencv2/shape.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/utility.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;


static vector<Point> simpleContour(const Mat& currentQuery, int n = 300)
{
	vector<vector<Point> > _contoursQuery;
	vector <Point> contoursQuery;
	findContours(currentQuery, _contoursQuery, RETR_LIST, CHAIN_APPROX_NONE);
	for (size_t border = 0; border<_contoursQuery.size(); border++)
	{
		for (size_t p = 0; p<_contoursQuery[border].size(); p++)
		{
			contoursQuery.push_back(_contoursQuery[border][p]);
		} 
	}


	
	// In case actual number of points is less than n
	int dummy = 0;
	for (int add = (int)contoursQuery.size() - 1; add<n; add++)
	{
		contoursQuery.push_back(contoursQuery[dummy++]); //adding dummy values
	}

	// Uniformly sampling
	//srand(time(0));
	//srand(1);
	//srand(time(NULL));

	random_shuffle(contoursQuery.begin(), contoursQuery.end());
	vector<Point> cont;
	for (int i = 0; i<n; i++)
	{
		cont.push_back(contoursQuery[i]);
	}
	return cont;
}
int main(int argc, char** argv)
{
	cv::Ptr <cv::HausdorffDistanceExtractor> mysc2 = cv::createHausdorffDistanceExtractor();
	//Mat query = imread("dataset/queries/u3/0.bmp", IMREAD_GRAYSCALE);
	for (int i = 9; i <47 ; i++){
		srand(1);
		string path = "dataset/queries/u9/0.bmp";//+ to_string("40") + ".bmp";
		string path1 = "database/u19/skels/right_hand/"+to_string(i) + ".bmp";

		Mat query = imread(path, IMREAD_GRAYSCALE);
		vector<Point> contQuery = simpleContour(query);
		Mat iiIm = imread(path1, IMREAD_GRAYSCALE);
		vector<Point> contii = simpleContour(iiIm);
		float dis = mysc2->computeDistance(contQuery, contii);
		cout << i << " with distance " << dis << endl;

	}
 	
	getchar();
	waitKey(0);
	return 0;
}
