#include "feature_extractor.h"

#include <iostream>
#include<vector>
#include<filesystem>
#include<fstream>

namespace fs = std::filesystem;
using path = fs::path;
namespace hist = descriptor::histogram;

std::pair<path, path> getPaths();

int main(int argc, char **argv) {

	std::clock_t t {std::clock()};
	std::pair<path, path> image_paths = getPaths();
	cv::Mat query_image = imread(image_paths.first, cv::IMREAD_COLOR);
	cv::Mat dataset_image;

	cv::Mat query_features = hist::getFeatureVector(std::move(query_image));
	cv::Mat temp_features;

	for (const auto &fname: fs::directory_iterator(image_paths.second)) {
		dataset_image = cv::imread(fname.path(), cv::IMREAD_COLOR);
		 temp_features = hist::getFeatureVector(std::move(dataset_image));
		std::cout << temp_features.size() << std::endl;
	}

	double time = static_cast<double>((std::clock() - t) / (CLOCKS_PER_SEC / 1000));
	std::cout << time << std::endl;
	return EXIT_SUCCESS;
}

std::pair<path, path> getPaths() {
	return std::make_pair("../../image/sample.jpg", "../../image/sample_dataset");
}

