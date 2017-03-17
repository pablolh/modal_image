#include <opencv2/opencv.hpp>

#include <stdio.h>
#include <unistd.h>
using namespace cv;
using namespace std;


int t = 180;
int t2 = 100;
int p = 10;
Ptr<BackgroundSubtractorMOG2> bs;

int main(int, char**) {
	Mat frame;
	Mat mask;
	Mat frame2;
	VideoCapture cap;
	cap.open(0);
	
	namedWindow("Mask", WINDOW_AUTOSIZE);
	namedWindow("Contour", WINDOW_AUTOSIZE);
	bs = createBackgroundSubtractorMOG2();
	bs->setHistory(400);
	//~ bs->setNMixtures(3);
	bs->setDetectShadows(false);
	//~ bs->setVarThreshold(10);
	//~ bs->setComplexityReductionThreshold(0);
	//~ bs->setBackgroundRatio(1);
	Mat frame0;
	
	vector<int> hull;
	vector<vector<Point>> contours;
	
	cap.read(frame0);
	while(true) {
		cap.read(frame);
		
		bs->apply(frame, mask);
		morphologyEx(mask, mask, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(4, 4)));
		morphologyEx(mask, mask, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(4, 4)));
		// bs->getBackgroundImage(frame2);
		//~ Canny(mask, frame2, t, t*3);
		findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		//~ drawContours(frame2, contours, 0, Scalar(0, 255, 255), CV_FILLED, 8);
		
		vector<Point2i> all;
		for(vector<Point2i> contour : contours) {
			for(Point2i p : contour) {
				all.push_back(p);
			}
		}
		//~ cout << all;
		imshow("Mask", mask);
		//~ imshow("Contour", frame2);
		convexHull(all, hull);
		Point2i pt0 = all[hull[0]];
		for (int i : hull) {
			line(frame, pt0, all[i], Scalar(255, 0, 0), 1,LINE_AA);
            pt0 = all[i];
		}
		
		//~ Vec4i defects;
		//~ convexityDefects(all, hull, defects);
		//~ cout << defects[0];
		
		imshow("Webcam", frame);
		waitKey(30);
	}
	
}
