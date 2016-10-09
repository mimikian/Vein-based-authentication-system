#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/shape/shape.hpp"
#include <iostream>

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

static void help()
{
	printf("\n"
		"This program demonstrates a method for vein authentication based on Hausdorff Distance\n"
		"The dataset include 14 images for 14 different users. \n");
}

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
	random_shuffle(contoursQuery.begin(), contoursQuery.end());
	vector<Point> cont;
	for (int i = 0; i<n; i++)
	{
		cont.push_back(contoursQuery[i]);
	}
	return cont;
}

int N = 14;

int main(int argc, char** argv)
{
	FILE *f = fopen("dataset/ShapeContextS1.txt", "w");
	
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}


	help();
	// Compare 2 images using shapecontext
	cv::Ptr <cv::ShapeContextDistanceExtractor> mysc = cv::createShapeContextDistanceExtractor();
	
	// Compare 2 images using HausdorffDistance 
	//cv::Ptr <cv::HausdorffDistanceExtractor> mysc = cv::createHausdorffDistanceExtractor();
	
	string datasetsPath = "dataset/dataset/u";
	string queriesPath = "dataset/queries/u";
	string imageExt = "0.bmp";
	int error = 0;
	for (int i = 10; i < N; i++){
		cout << "========================" << endl;
		fprintf(f, "========================\n");
		cout << "User " + to_string(i) + ": \n";
		fprintf(f, "User %i :\n", i);
		string queryPath = queriesPath + to_string(i) + "/" + imageExt;
		Mat query = imread(queryPath, IMREAD_GRAYSCALE);
		srand(1);
		vector<Point> queryContour = simpleContour(query);
		float bestMatch = FLT_MAX;
		int bestMatchIndex = -1;
		for (int j = 0; j < N; j++){
			string datasetPath = datasetsPath + to_string(j) + "/1.bmp";

			//		string datasetPath = datasetsPath + to_string(j) + "/" + imageExt;
			Mat dataset = imread(datasetPath, IMREAD_GRAYSCALE);
			vector<Point> datasetContour;
			srand(1);
			vector<Point> dummy = simpleContour(query);
			datasetContour = simpleContour(dataset);
			float dis = mysc->computeDistance(datasetContour,queryContour);
			cout << " distance between user " << i << " and user " << j << " is: " << dis << std::endl;
			fprintf(f, "  distance between user %i and user %i is :  %f \n", i, j, dis);
			if (dis < bestMatch){
				bestMatchIndex = j;
				bestMatch = dis;
			}

		}
		if (i != bestMatchIndex){
			error++;
		}
		cout << "Thes best match with user " + to_string(i) + " is user " << bestMatchIndex << " with value " << bestMatch << endl;
		fprintf(f, "The best match with user %i is user %i with value  %f\n", i, bestMatchIndex, bestMatch);

	}

	cout << "============ \n error is "<< error << endl;
	fprintf(f, "========== \n error is %i",error);
	fclose(f);
	std::getchar();
	return 0;
}
