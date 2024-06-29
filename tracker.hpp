#ifndef TRACKER_HPP
#define TRACKER_HPP

#include "opencv2/opencv.hpp"

bool trackerFunction(const cv::Mat& frame, cv::Mat& outputFrame);

#endif // TRACKER_HPP
