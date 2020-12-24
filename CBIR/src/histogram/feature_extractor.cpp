/*
* feature_extractor.cpp
*
*  Created on: 22-Aug-2020
*      Author: abhishek
*/

#include "feature_extractor.h"
namespace d = descriptor;
namespace hist = descriptor::histogram;

int hist_size[3] {50, 32, 10};
const float h_ranges[2] {0, 256};
const float s_ranges[2] {0, 180};
const float v_ranges[2] {0, 256};
const float* ranges[3] {h_ranges, s_ranges, v_ranges};
const int channels[3] {0, 1, 2};

template<int size>
void hist::setBins(const int (&&bins)[size]) {
	hist_size  = bins;
}

cv::Mat hist::extract(cv::Mat &&src, d::FEATURE_ALGORITHM algorithm) { // @suppress("Member declaration not found")

	cv::Mat hist_base;
	cv::Mat mask;
	try {
		cv::calcHist( &src, 1, channels, mask, hist_base, 3, hist_size, ranges, true, false);
		cv::normalize(hist_base, hist_base, 0, 1, cv::NORM_MINMAX, -1, mask);
		hist_base = hist_base.reshape(0, 1);
	}
	catch(std::exception &e) {
		e.what();
	}
	return hist_base;
}


cv::Mat hist::getFeatureVector(cv::Mat &&src) {

	int height{src.rows};
	int width{src.cols};
	int h{static_cast<int>(height/3)};
	int w{static_cast<int>(width/3)};
	int h2{h + h};
	int w2{w + w};

	int segments[9][2][2]{ {{0, 0}, {w, h}},
			{{w, 0}, {w2, h}},
			{{w2, 0}, {width, h}}, //1st level

			{{0, h}, {w, h2}},
			{{w, h}, {w2, h2}},
			{{w2, h}, {width, h2}}, //2nd level

			{{0, h2}, {w, height}},
			{{w, h2}, {w2, height}},
			{{w2, h2}, {width, height}} //3rd level
	};

	int nMasks = 9;
	cv::Mat feature_vector, temp, mask;
	for (int i=0; i<nMasks; ++i) {
		cv::Point2i pt1(segments[i][0][0], segments[i][0][1]);
		cv::Point2i pt2(segments[i][1][0], segments[i][1][1]);
		cv::Rect const mask(pt1, pt2);
		cv::Mat roi = src(mask);
		temp = extract(std::move(roi));
		feature_vector.push_back(temp);
	}

	feature_vector = feature_vector.reshape(0, 1);
	return feature_vector;
}






