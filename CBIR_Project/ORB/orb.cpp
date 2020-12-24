/*
 * orb_main.cpp
 *
 *  Created on: 09-Sep-2020
 *      Author: abhishek
 */

/*
 * TO DO
 *
 *
 * 1. Find the biggest contour. And use that for further processing
 * 2. Downloading the images for at least 10 objects each having 15 images.
 * Download image with only single object and ambiguous as well
 * 3.
 * . Performing the operation on a directory and storing
 * it in a yml file refer to the histogram file io code.
 *
 * */

#include "orb.h"
#include <iostream>
#include <algorithm>
auto CompareKeyPoints = [](const cv::KeyPoint &k1, const cv::KeyPoint &k2) {
	return k1.response > k2.response;
};

const cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
const cv::Ptr<cv::DescriptorExtractor> descriptor = cv::ORB::create();
//const cv::Ptr<cv::DescriptorMatcher> matcher  = cv::DescriptorMatcher::create ( "BruteForce-Hamming" );
const cv::Ptr<cv::DescriptorMatcher> matcher =
		cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);

cv::Mat getContour(cv::Mat &&img) {

	const int thresh = 160;
	cv::Mat canny_output;
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::resize(img, img, cv::Size(300, 300));
//	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

	cv::blur(img, img, cv::Size(3, 3));
	// Detect edges using canny
	cv::Canny(img, canny_output, thresh, thresh*2, 3);
	// Find contours
	cv::findContours(canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

//	sort(contours.begin(), contours.end(), [](const std::vector<cv::Point> &c1, const std::vector<cv::Point> &c2) {
//			return cv::contourArea(c1, false) > cv::contourArea(c2, false);
//	});
//
//	std::vector<std::vector<cv::Point>>  mainContours(contours.begin(), contours.begin() + 5);
	cv::Mat drawing = cv::Mat::zeros(canny_output.size(), CV_8UC3);
	cv::drawContours(drawing, contours, -1, cv::Scalar(255, 255, 255));

//	cv::imshow("c", drawing);
//	cv::waitKey(0);
	return drawing;
}

cv::Mat getFeatureDescriptors(const cv::Mat &&contour, int vec_size) {

	cv::Mat descriptors;
	std::vector<cv::KeyPoint> keypoints;
	int needed_size{vec_size * 128};

	detector->detect(contour, keypoints);

	std::sort(keypoints.begin(), keypoints.end(), CompareKeyPoints);
	detector->compute(contour, keypoints, descriptors);

	descriptors = descriptors.reshape(1, 1);

	if (descriptors.cols >= needed_size)
		cv::resize(descriptors, descriptors, cv::Size(needed_size, 1));
	else
		cv::hconcat(descriptors, cv::Mat::zeros(1, needed_size - descriptors.cols, descriptors.type()), descriptors);

	return descriptors;
}


void performMatch(cv::Mat desc1, cv::Mat desc2) {

	cv::tbm::CosDistance cos(desc1.size());
	cos.compute(desc1, desc2);




//    std::vector<std::vector<cv::DMatch>> knn_matches;
//    if(desc1.type() != CV_32F)
//        desc1.convertTo(desc1, CV_32F);
//
//    if(desc2.type() != CV_32F)
//        desc2.convertTo(desc2, CV_32F);
//
//    matcher->knnMatch(desc1, desc2, knn_matches, 2);
//
//	const float ratio_thresh = 0.7f;
//	std::vector<cv::DMatch> good_matches;
//	for (size_t i = 0; i < knn_matches.size(); i++) {
//		if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
//			good_matches.push_back(knn_matches[i][0]);
//	}
//	std::cout << knn_matches.size() <<std::endl;
}
