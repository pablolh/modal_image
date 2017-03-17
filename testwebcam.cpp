#include <opencv2/opencv.hpp>

#include <stdio.h>
#include <unistd.h>
using namespace cv;
using namespace std;


int t = 180;
int t2 = 100;
int p = 10;
int h = 400;
Ptr<BackgroundSubtractorMOG2> bs;

static void trackmask( int, void* )
{
	bs->setVarThreshold(t2/5);
}
static void trackhistory( int, void* )
{
	bs->setHistory(h);
}

int main(int, char**) {
	Mat frame;
	Mat mask;
	Mat frame2;
	VideoCapture cap;
	cap.open(0);
	
	namedWindow("Mask", WINDOW_AUTOSIZE);
	namedWindow("Contour", WINDOW_AUTOSIZE);
	bs = createBackgroundSubtractorMOG2();
	bs->setHistory(h);
	bs->setNMixtures(3);
	bs->setDetectShadows(false);
	bs->setVarThreshold(20);
	//~ bs->setComplexityReductionThreshold(0);
	//~ bs->setBackgroundRatio(1);
	Mat frame0;

	cap.read(frame0);
	while(true) {
		cap.read(frame);
		imshow("webcam", frame);
		bs->apply(frame, mask);
		morphologyEx(mask, mask, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(4, 4)));
		morphologyEx(mask, mask, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));
		// bs->getBackgroundImage(frame2);
		Canny(mask, frame2, t, t*3);
		imshow("Mask", mask);
		imshow("Contour", frame2);
		waitKey(30);
	}
	
}
