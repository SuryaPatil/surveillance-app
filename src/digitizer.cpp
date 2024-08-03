#include "opencv2/opencv.hpp"
using namespace cv;
#include <iostream>
#include <sstream> // For std::ostringstream
#include <string>  // For std::string
#include <pthread.h> 
#include "source.hpp"

//Mat buffer[BUF_SIZE];
void *capture(void *param)
{
    VideoCapture cap(0); // open the default camera (use 0 for the default camera, -1 may not be a valid index)
    if (!cap.isOpened()) { // check if we succeeded
        std::cerr << "Error: Could not open camera." << std::endl;
        return nullptr;
    }

    Mat frame;
    Mat analyzedFrame;
    int frameNumber = 0;
    std::string windowName = "Camera Frame";

    namedWindow(windowName, WINDOW_AUTOSIZE);

    while (running) {
        cap >> frame; // capture a new frame
        if (frame.empty()) {
            std::cerr << "Error: Could not read frame from camera" << std::endl;
            break;
        }

        pthread_mutex_lock (&m);
		if (numIndex > BUF_SIZE) exit(1);	/* overflow */
		while (numIndex == BUF_SIZE)			/* block if buffer is full */
			pthread_cond_wait (&c_prod, &m);
		/* if executing here, buffer not full so add element */
		buffer[addIndex] = frame;
		addIndex = (addIndex+1) % BUF_SIZE;
		numIndex++;
		pthread_mutex_unlock (&m);
		pthread_cond_signal (&c_cons);

        imshow(windowName,frame);
	//	printf ("producer: inserted %d\n", frameNumber);  fflush (stdout);
        frameNumber += 1;
    }

    cap.release();
    destroyAllWindows();
    printf("digitizer thread returning\n");
    return nullptr;
}