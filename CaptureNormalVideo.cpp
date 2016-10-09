#include <opencv\cv.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")
#define default_buflen 1024

using namespace std;
using namespace cv;

#define default_port "1234"

int main(int argc, char** argv)
{
	Mat capture;
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "Cannot connect to camera" << endl;
		getchar();
		return -1;
	}

	namedWindow("Display", WINDOW_AUTOSIZE);

	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT);

	Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));

	int codec = cv::VideoWriter::fourcc('P','I','M','1');
	VideoWriter oVideoWriter("C:\out.avi", codec,20, frameSize, true);

	if (!oVideoWriter.isOpened())
	{
		cout << "ERROR: Failed to write the video" << endl;
		return -1;
	}

	while (true)
	{
		Mat frame;

		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "ERROR: Cannot read a frame from video file" << endl;
			break;
		}
		oVideoWriter.write(frame); //writer the frame into the file

		imshow("Display", frame);

		if (waitKey(10) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
}
