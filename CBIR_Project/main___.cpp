///*
// * mask.cpp
// *
// *  Created on: 20-Aug-2020
// *      Author: abhishek
// */
//
//
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/imgproc.hpp>
//
//#include <iostream>
//#include<vector>
//
//using uchar = unsigned char;
//int h_bins {50};
//int s_bins {32};
//int v_bins {10};
//int hist_size[] { h_bins, s_bins, v_bins };
//
//float h_ranges[] { 0, 256 };
//float s_ranges[] { 0, 180 };
//float v_ranges[] { 0, 256 };
//float x;
//const float* ranges[] = {h_ranges, s_ranges, v_ranges};
//int channels[] = {0, 1, 2};
//
//cv::Mat colorHistogram(cv::Mat &src) {
//
//	cv::Mat hist_base;
//	cv::Mat mask;
//	cv::calcHist( &src, 1, channels, cv::Mat(), hist_base, 3, hist_size, ranges, true, false);
//	cv::normalize(hist_base, hist_base, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
//	hist_base = hist_base.reshape(0, 1);
//	return hist_base;
//}
//
//int main() {
//	cv::Mat src = cv::imread("image/autumn.jpeg", cv::IMREAD_COLOR);
//	if (!src.data) {
//		std::cout << "Error";
//		return EXIT_FAILURE;
//	}
//	int height{src.rows};
//	int width{src.cols};
//	int h{static_cast<int>(height/3)};
//	int w{static_cast<int>(width/3)};
//	int h2{h + h};
//	int w2{w + w};
//
//	int segments[9][2][2]{ {{0, 0}, {w, h}},
//			{{w, 0}, {w2, h}},
//			{{w2, 0}, {width, h}}, //1st level
//
//			{{0, h}, {w, h2}},
//			{{w, h}, {w2, h2}},
//			{{w2, h}, {width, h2}}, //2nd level
//
//			{{0, h2}, {w, height}},
//			{{w, h2}, {w2, height}},
//			{{w2, h2}, {width, height}} //3rd level
//	};
//
//	int nMasks = 9;
//	cv::Mat feature_vector, temp, mask;
//	std::cout << "HELLO THERE\n";
//	for (int i=0; i<nMasks; ++i) {
//		cv::Point2i pt1(segments[i][0][0], segments[i][0][1]);
//		cv::Point2i pt2(segments[i][1][0], segments[i][1][1]);
//		cv::Rect const mask(pt1, pt2);
//		cv::Mat roi = src(mask);
//		temp = colorHistogram(roi);
//		feature_vector.push_back(temp);
//	}
//
//	feature_vector = feature_vector.reshape(0, 1);
//	std::cout << feature_vector.size() << std::endl;
//
//	return EXIT_SUCCESS;
//}
