#include "opencv2/opencv.hpp"
using namespace cv;
#include <iostream>
#include <sstream> // For std::ostringstream
#include <string>  // For std::string

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera (use 0 for the default camera, -1 may not be a valid index)
    if (!cap.isOpened()) { // check if we succeeded
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }

    Mat frame;
    int frameNumber = 0;
    std::string windowName = "Camera Frame";

    namedWindow(windowName, WINDOW_AUTOSIZE);

    while (true) {
        cap >> frame; // capture a new frame
        if (frame.empty()) {
            std::cerr << "Error: Could not read frame from camera" << std::endl;
            break;
        }

        if (frameNumber == 200){
            break;
        }

        // Save the frame as an image file
        std::ostringstream filename;
        filename << "frame_" << frameNumber << ".png";
        imwrite(filename.str(), frame);
        frameNumber++;

        // Display the frame
        imshow(windowName, frame);

        // Exit if ESC key is pressed
        if (waitKey(30) == 27) {
            std::cout << "ESC key pressed by user. Exiting..." << std::endl;
            break;
        }
    }

    cap.release();
    destroyAllWindows();
    return 0;


    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}