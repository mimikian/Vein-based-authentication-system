#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/shape/shape.hpp"
#include <iostream>

#include <Windows.h>

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
		"This program demonstrates a method for shape comparisson based on Shape Context\n"
		"You should run the program providing a number between 1 and 20 for selecting an image in the folder ../data/shape_sample.\n"
		"Call\n"
		"./shape_example [number between 1 and 20]\n\n");
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

vector<string> get_all_files_names_within_folder(string folder)
{
	vector<string> names;
	char search_path[200];
	sprintf(search_path, "%s*.*", folder.c_str());
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

int main(int argc, char** argv)
{
	help();
	
	Size sz2Sh(300, 300);
	stringstream queryName;
	auto y = 1;
	int x []= { 1, 2 };
	
	vector<int> array0;
	array0.push_back(14);
	array0.push_back(15);
	array0.push_back(16);
	array0.push_back(17);
	array0.push_back(19);
	array0.push_back(20);
	array0.push_back(21);
	array0.push_back(22);
	array0.push_back(23);
	array0.push_back(24);
	array0.push_back(25);
	array0.push_back(26);
	array0.push_back(27);
	array0.push_back(28);
	array0.push_back(29);
	array0.push_back(30);

	vector<int> array1;
	array1.push_back(8);
	array1.push_back(9);
	array1.push_back(16);
	array1.push_back(25);
	array1.push_back(26);
	array1.push_back(53);
	array1.push_back(56);
	array1.push_back(64);
	array1.push_back(68);
	array1.push_back(69);

	cv::Ptr <cv::HausdorffDistanceExtractor> mysc = cv::createHausdorffDistanceExtractor();
	//cv::Ptr <cv::ShapeContextDistanceExtractor> mysc = cv::createShapeContextDistanceExtractor();

	for (int i = 0; i < array0.size(); i++){
		string a = to_string(array0[i]);
		printf("Number %d \n", array0[i]);

		for (int j = 0; array1.size(); j++) {
			string b = to_string(array1[j]);

			Mat query = imread("database/u0/skels_query/left_hand/"+a+".bmp", IMREAD_GRAYSCALE);
			Mat queryToShow;
			resize(query, queryToShow, sz2Sh);
			imshow("QUERY", queryToShow);
			moveWindow("TEST", 0, 0);
			vector<Point> contQuery = simpleContour(query);
			

			Mat iiIm = imread("database/u0/skels_training/"+b+".bmp", IMREAD_GRAYSCALE);
			Mat iiToShow;
			resize(iiIm, iiToShow, sz2Sh);
			imshow("TEST", iiToShow);
			vector<Point> contii = simpleContour(iiIm);
			float distance = mysc->computeDistance(contQuery, contii);
			printf("=== Number %d distance is ", array1[j]);
			cout << distance << endl;
		}

	waitKey(0);
	return 0;
}
