/*
 * RangeFinder.h
 *
 *  Created on: Nov 25, 2018
 *      Author: Elijah Mt. Castle
 */

#ifndef SRC_RANGEFINDER_H_
#define SRC_RANGEFINDER_H_
#include <opencv2/opencv.hpp>
#include <string>

class RangeFinder {
public:

	RangeFinder();//Default Constructor
	RangeFinder(std::string path, double focal, double width);//Parameter Constructor
	RangeFinder(bool dev,std::string path, double dist, double width);//Dev Constructor


	void Begin();//starts the process
	double getDistance()const;//returns distance


private:

	cv::Mat _src;
	int _width;
	double _FOCAL;
	double _dist=-1;


	void Show(cv::Mat img,std::string title);//shows the images scaled down to load faster
	cv::Mat Clean();//returns image with some thresholding and blurring
	void Distance();//finds distance
	void focalFind();//finds the focal in pixels/inch
};

#endif /* SRC_RANGEFINDER_H_ */
