#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;


class ImgProcessor {
private:
	Mat src;
public:
	void set_values(Mat);
	Mat run(void);
};