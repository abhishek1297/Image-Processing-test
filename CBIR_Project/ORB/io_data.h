/*
 * io_csv.h
 *
 *  Created on: 25-Aug-2020
 *      Author: abhishek
 */
#pragma once
#ifndef SRC_HISTOGRAM_IO_DATA_H_
#define SRC_HISTOGRAM_IO_DATA_H_
#include <string>
#include<opencv2/imgproc.hpp>
#include<filesystem>
#include<fstream>

namespace fs = std::filesystem;
using path = fs::path;

class FileIO {
	cv::FileStorage fs;
public:
	FileIO(std::string fname, bool write_mode=false, bool clear=false);
	~FileIO();
	cv::Mat read(const std::string &id);
	void write(std::string id, cv::Mat &&mat);
};

#endif /* SRC_HISTOGRAM_IO_DATA_H_ */
