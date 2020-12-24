/*
 * io_file.cpp
 *
 *  Created on: 25-Aug-2020
 *      Author: abhishek
 */

#include "io_data.h"

FileIO::FileIO(std::string fname, bool write_mode, bool clear) {

	if (clear && write_mode) {
		std::ofstream out {fname, std::ios::trunc};
		out.close();
	}
	fs.open(fname, (write_mode) ? cv::FileStorage::APPEND : cv::FileStorage::READ);

}

FileIO::~FileIO() {
	fs.release();
}
void FileIO::write(std::string id, cv::Mat &&mat) {
	fs << "_" + id << mat;
}

cv::Mat FileIO::read(const std::string &id) {
	cv::Mat mat;
	fs["_" + id] >> mat;
	return mat;
}

