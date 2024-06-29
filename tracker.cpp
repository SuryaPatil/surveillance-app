#include "tracker.hpp"
#include <vector>

using namespace cv;
using namespace std;

bool trackerFunction(const Mat& frame, Mat& outputFrame) {
    // Convert frame to HSV color space
    Mat hsvFrame;
    cvtColor(frame, hsvFrame, COLOR_BGR2HSV);

    // Threshold the HSV image to get only white colors
    Mat mask;
    inRange(hsvFrame, Scalar(0, 0, 200), Scalar(180, 55, 255), mask);

    // Find contours
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(mask, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    bool waterBottleDetected = false;

    // Copy the input frame to output frame to draw bounding boxes
    frame.copyTo(outputFrame);

    for (size_t i = 0; i < contours.size(); i++) {
        Rect boundingRect = cv::boundingRect(contours[i]);
        double aspectRatio = (double)boundingRect.height / (double)boundingRect.width;

        // Simple heuristic for water bottle detection based on aspect ratio and size
        if (aspectRatio > 1.5 && boundingRect.height > 50) {
            rectangle(outputFrame, boundingRect, Scalar(255, 0, 0), 2);
            waterBottleDetected = true;
        }
    }

    return waterBottleDetected;
}
