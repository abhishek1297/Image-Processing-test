/*
 * orb.h
 *
 *  Created on: 09-Sep-2020
 *      Author: abhishek
 */

#ifndef ORB_ORB_H_
#define ORB_ORB_H_
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/tracking/tracking_by_matching.hpp>
#include <vector>

struct CompareKeyPoints;

cv::Mat getContour(cv::Mat &&img);
cv::Mat getFeatureDescriptors(const cv::Mat &&contour, int vec_size = 32);
void performMatch(cv::Mat desc1, cv::Mat desc2);

#endif /* ORB_ORB_H_ */
