/*
 * test.cpp
 *
 *  Created on: 08-Sep-2020
 *      Author: abhishek
 */


#include <iostream>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


Mat getContour(Mat mat) {
	Mat canny_output, src_gray;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	int thresh = 100;

	cvtColor(mat, src_gray, COLOR_BGR2GRAY);
	Canny( src_gray, canny_output, thresh, thresh*2, 3 );
	/// Find contours
	findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

	/// Draw contours
	Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
	for( int i = 0; i< contours.size(); i++ )
	 {
	   Scalar color = Scalar(255, 0, 0);
	   drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
	 }

	return drawing;
}


int compareORB(Mat img1, Mat img2) {
	int val = -1;

	return val;
}

int main() {



	return EXIT_SUCCESS;
}
