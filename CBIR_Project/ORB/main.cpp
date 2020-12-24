/*
 * main.cpp
 *
 *  Created on: 09-Sep-2020
 *      Author: abhishek
 */


#include "orb.h"
#include "io_data.h"
#include <filesystem>
#include <set>
cv::Mat getFeatures(std::string path);
void storeFeatures(FileIO &fio, std::string dataset_path);
void compareFeatures(std::string query_path, std::string dataset_path, FileIO &fio);


using pair_sd = std::pair<std::string, double>;


struct compareDistance {
	inline bool operator() (const pair_sd &p1, const pair_sd &p2) const {
		return p1.second < p2.second;
	}
};
std::set<pair_sd, compareDistance> sorted_set;

int main () {

	std::string query_path{"/home/abhishek/Downloads/query_data/shirt_sketch1.png"};
	std::string dataset_path{"/home/abhishek/Downloads/sample_data"};
	FileIO fio(dataset_path  + "/features.yml");
//	FileIO fio(dataset_path  + "/features.yml", true, true);
	cv::Mat img = cv::imread(query_path, cv::IMREAD_GRAYSCALE);

//	compareFeatures(query_path, dataset_path, fio);
//	storeFeatures(fio, dataset_path);
//	for (auto p: sorted_set) {
//		std::cout << p.first << ": " << p.second << std::endl;
//	}
//	getFeatures(query_path);
	return 0;
}


cv::Mat getFeatures(std::string path) {

	cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);
	cv::Mat c;
	cv::Mat desc;
	if (img.data) {
		c = getContour(std::move(img));
		desc = getFeatureDescriptors(std::move(c));
	}
	return desc;
}

void storeFeatures(FileIO &fio, std::string dataset_path) {

	cv::Mat features;
	path id;

	for (auto &di: fs::directory_iterator(path(dataset_path))) {
		if (!di.is_directory()) {
			id = di.path();
			features = getFeatures(id.string());
			if (!features.empty())
				fio.write(id.stem().string(), std::move(features));
		}
	}
}


void compareFeatures(std::string query_path, std::string dataset_path, FileIO &fio) {

	cv::Mat against_features;
	cv::Mat query_features(getFeatures(query_path));
	cv::tbm::CosDistance cos(query_features.size());

	path id;
	for (auto &di: fs::directory_iterator(path(dataset_path))) {
		if (!di.is_directory()) {
			id = di.path();
//			std::cout << id.stem().string() << ": ";
			against_features = fio.read(id.stem().string());
			if (!against_features.empty()) {
				sorted_set.insert(std::make_pair(id.stem().string(),
						cos.compute(query_features, against_features)));
			}
		}
	}
}
