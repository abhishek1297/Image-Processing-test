/*
* feature_extractor.h
*
*  Created on: 20-Aug-2020
*      Author: abhishek
*/
#pragma once

#ifndef FEATURE_EXTRACTOR_H_
#define FEATURE_EXTRACTOR_H_

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

namespace descriptor {
	enum FEATURE_ALGORITHM {COLOR_HIST, SIFT, SURF, FLANN};
	class FeatureSelector {};

	namespace histogram {
		template<int size>
		void setBins(const int (&&bins)[size]);
		cv::Mat extract(cv::Mat &&src, FEATURE_ALGORITHM algorithm = COLOR_HIST);
		cv::Mat getFeatureVector(cv::Mat &&src);
//		bool compare(cv::Mat &query, cv::Mat &&other);
	};
};

#endif /* FEATURE_EXTRACTOR_H_ */
