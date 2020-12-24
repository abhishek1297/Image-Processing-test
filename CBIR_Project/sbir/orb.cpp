/*
 * sbir.cpp
 *
 *  Created on: 07-Sep-2020
 *      Author: abhishek
 */

#include <iostream>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

Mat getContour(Mat img) {
	const int thresh = 255;
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	blur(img, img, Size(3, 3));
	/// Detect edges using canny
	Canny( img, canny_output, thresh, thresh*2, 3 );
	/// Find contours
	findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
	Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
	drawContours( drawing, contours, -1, Scalar(255, 255, 255));//8, hierarchy, 0, Point() );
//	imshow("drawing", drawing);
//	waitKey(0);
	return drawing;
}

int main ( int argc, char** argv )
{
    //-- 读取图像
	string query = "/home/abhishek/Downloads/shoe_sketch.png";
	string other = "/home/abhishek/Downloads/shoe3.jpg";

    Mat img_1 = imread ( query, IMREAD_GRAYSCALE );
    Mat img_2 = imread ( other, IMREAD_GRAYSCALE );
    resize(img_1,img_1, Size(300, 300));
    resize(img_2, img_2, Size(300, 300));
    img_1 = getContour(img_1);
    img_2 = getContour(img_2);

    //    //-- 初始化
    std::vector<KeyPoint> keypoints_1, keypoints_2;
    Mat descriptors_1, descriptors_2;
    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();

    Ptr<DescriptorMatcher> matcher  = DescriptorMatcher::create ( "BruteForce-Hamming" );

    //-- 第一步:检测 Oriented FAST 角点位置
    detector->detect ( img_1,keypoints_1 );
    detector->detect ( img_2,keypoints_2 );

    //-- 第二步:根据角点位置计算 BRIEF 描述子
    descriptor->compute ( img_1, keypoints_1, descriptors_1 );
    descriptor->compute ( img_2, keypoints_2, descriptors_2 );

    Mat outimg1;
    drawKeypoints( img_1, keypoints_1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
//    imshow("ORB特征点",outimg1);

    //-- 第三步:对两幅图像中的BRIEF描述子进行匹配，使用 Hamming 距离
    vector<DMatch> matches;
    //BFMatcher matcher ( NORM_HAMMING );
    matcher->match ( descriptors_1, descriptors_2, matches );

    //-- 第四步:匹配点对筛选
    double min_dist=10000, max_dist=0;

    //找出所有匹配之间的最小距离和最大距离, 即是最相似的和最不相似的两组点之间的距离
    for ( int i = 0; i < descriptors_1.rows; i++ )
    {
        double dist = matches[i].distance;
        if ( dist < min_dist ) min_dist = dist;
        if ( dist > max_dist ) max_dist = dist;
    }

    printf ( "-- Max dist : %f \n", max_dist );
    printf ( "-- Min dist : %f \n", min_dist );

    //当描述子之间的距离大于两倍的最小距离时,即认为匹配有误.但有时候最小距离会非常小,设置一个经验值30作为下限.
    std::vector< DMatch > good_matches;
    for ( int i = 0; i < descriptors_1.rows; i++ )
    {
        if ( matches[i].distance <= max ( 2*min_dist, 30.0 ) )
        {
            good_matches.push_back ( matches[i] );
        }
    }

    //-- 第五步:绘制匹配结果
    Mat img_match;
    Mat img_goodmatch;
    drawMatches ( img_1, keypoints_1, img_2, keypoints_2, matches, img_match );
    drawMatches ( img_1, keypoints_1, img_2, keypoints_2, good_matches, img_goodmatch );

    imshow ( "1", img_match );
    imshow ( "2", img_goodmatch );
    waitKey(0);

    return 0;
}
