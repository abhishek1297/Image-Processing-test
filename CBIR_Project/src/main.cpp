#include "histogram/feature_extractor.h"
#include "io_data.h"
#include <iostream>
#include <set>
#include<algorithm>

namespace hist = descriptor::histogram;
namespace fs = std::filesystem;
using path = fs::path;
using img_dist_pair = std::pair<std::string, double>;

struct Comparator {
	bool operator() (const img_dist_pair &p1, const img_dist_pair &p2) const {
		return p1.second < p2.second;
	}
};

void storeFeatureVectors (const path &directory, const std::string &to_file, bool clear=false);
std::set<img_dist_pair, Comparator> search(const path &feature_file, const path &directory, const cv::Mat &&query_features, int limit=5);

//int main(int argc, char **argv) {
//
//	path pictures {"/home/abhishek/Downloads"};
//	path dataset_path  = pictures / "jpg";
//	path query_path  = dataset_path / "132501.jpg";
//	path feature_file = dataset_path / "features_603200.yml";
//
//	double time;
//
//	cv::Mat query_image = cv::imread(query_path.c_str(), cv::IMREAD_COLOR);
//	cv::Mat query_features = hist::getFeatureVector(std::move(query_image));
//
//	std::clock_t t = std::clock();
//	std::set<img_dist_pair, Comparator> image_results = search(feature_file, dataset_path, std::move(query_features));
//	time = static_cast<double>((std::clock() - t) / (CLOCKS_PER_SEC));
//	std::cout << time;
//	for(auto p: image_results) {
//		std::cout << p.first << "-> " << p.second << std::endl;
//		cv::Mat img = cv::imread(p.first, cv::IMREAD_COLOR);
//		cv::resize(img, img, cv::Size(640, 480));
//		cv::imshow("ss", img);
//		cv::waitKey(0);
//	}
//	return EXIT_SUCCESS;
//}


void storeFeatureVectors (const path &directory, const std::string &to_file, bool clear) {

	if (fs::exists(directory)) {
		std::clock_t t = std::clock();
		path csv_path  = directory / to_file;
		cv::Mat img, temp_features;
		FileIO fio{csv_path.c_str(), true, clear};

		for (const path &f: fs::directory_iterator(directory)) {
			std::string id = f.c_str();
			std::string fname = f.filename();
			if (fname == to_file)
				continue;
			img = cv::imread(id, cv::IMREAD_COLOR);
			if (img.data) {
				temp_features = hist::getFeatureVector(std::move(img));
				fio.write(f.stem(), std::move(temp_features));
			}
		}
		t = std::clock() - t;
		std::cout << "Time: " << t / CLOCKS_PER_SEC << std::endl;
	}
}


std::set<img_dist_pair, Comparator> search(const path &feature_file, const path &directory, const cv::Mat &&query_features, int limit) {

	int total = limit;
	const double threshold = 0.7;
	std::string stem, id;
	double distance;
	std::set<img_dist_pair, Comparator> image_results;
	cv::Mat image_features;
	if (!fs::exists(feature_file))
		storeFeatureVectors(directory, feature_file, false);
	FileIO fio{feature_file.c_str()};

	for (const path &f : fs::directory_iterator(directory)) {
		stem = f.stem();
		id = "_" + stem;
		image_features = fio.read(id);
		if (image_features.data) {
			distance = cv::compareHist(query_features, image_features, cv::HISTCMP_BHATTACHARYYA);
			if (distance <= threshold) {
				image_results.insert(std::make_pair(f.string(), distance));
				--total;
			}
			if (total == 0)
				break;
		}
	}
	return image_results;
}
