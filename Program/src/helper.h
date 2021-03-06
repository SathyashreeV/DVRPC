#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include "opencv2/opencv.hpp" // OpenCV 2.4.5


// Exits if input is invalid.
void checkInputs(cv::VideoCapture& v);
void checkInputs(cv::VideoCapture& v, int startTime, int duration);

// Get width, height, and number of frames.
void getVidInfo(cv::VideoCapture& v, int& height, int& width, int& nFrames);
void getVidInfo(cv::VideoCapture& v, int& height, int& width, int& nFrames, int& fps);

// OpenCV fails to read fps on some versions on some OS on some videos.
// This is just a wrapper.
int getFps(cv::VideoCapture& v);

// Skip to frame f.
void skipFrames(cv::VideoCapture& v, int f);

// bgMean, bgCov must be empty.
void loadBackground(const std::string& fileName, std::vector<cv::Mat>& bgMean, std::vector<cv::Mat>& bgCov);

// im		H x W (8UC3)
// bgMean	(H*W) 1 x 3 (64F)
// bgInvCov	(H*W) 3 x 3 (64F)
// thresh	Within range [0, 255]
// bw		H x W (8U)
void imMahalDist(const cv::Mat& im, const std::vector<cv::Mat>& bgMean, const std::vector<cv::Mat>& bgInvCov, const double& thresh, cv::Mat& bw);

// Compute greyscale, and find points (Good-Features-to-Track).
// frame	H x W (8UC3)
// nPoints	> 0
// points	nPoints x 1 (32FC2)
void getPoints(const cv::Mat& frame, int nPoints, cv::Mat& points);

// points	N x 1 (32FC2)
// bw		H x W (8U)
// isFG		N x 1 (8U)
// isWithin N x 1 (8U)
void getImageValuesAt(const cv::Mat& points, const cv::Mat& bw, cv::Mat& isFG, cv::Mat& isWithin);

void dispMatInfo(const cv::Mat& m);

// KLT using calcOpticalFlowPyrLK with forward-backward method like
// vision.PointTracker in MATLAB.
// prevImg	H x W (8UC3)
// nextImg	H x W (8UC3)
// prevPts	N x 1 (32FC2)
// nextPts	N x 1 (32FC2)
// status	nTracking x 1 (8U)
void klt(const cv::Mat& prevImg, const cv::Mat& nextImg, const cv::Mat& prevPts,
		 cv::Mat& nextPts, cv::Mat& status);

void loadTrajectories(const std::string& fileName, std::vector< std::vector<float> >& trajsX, std::vector< std::vector<float> >& trajsY, std::vector<int>& trajsStart, int& frameStart, int& frameEnd);

// Get time in seconds.
double getSec(const double& t0, const double& t1);

// This is because C++11 is not used (to_string() or itoa).
std::string to_string(int i);

#endif /* HELPER_H */
