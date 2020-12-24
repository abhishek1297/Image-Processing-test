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
#include <opencv2/cudaimgproc.hpp>
#include <vector>

namespace descriptor {
	enum FEATURE_ALGORITHM {COLOR_HIST, SIFT, SURF, FLANN};
	class FeatureSelector {};

	namespace histogram {
		cv::Mat extract(cv::Mat &&src);
		cv::Mat getFeatureVector(cv::Mat &&src);
	};
};

#endif /* FEATURE_EXTRACTOR_H_ */
