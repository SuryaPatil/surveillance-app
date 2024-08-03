#include <vector>
#include "source.hpp"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace cv;
using namespace std;

void *trackerFunction(void *param) {
    int j = 0;
    int frameNumber = 0;
    int numTrue = 0;
    int numFalse = 0;
    std::srand(std::time(0));
    while (running){

        pthread_mutex_lock (&m);
		if (numIndex < 0) exit(1);   /* underflow */
		while (numIndex == 0)		/* block if buffer empty */
			pthread_cond_wait (&c_cons, &m);
		/* if executing here, buffer not empty so remove element */
		Mat frame = buffer[remIndex];
		remIndex = (remIndex+1) % BUF_SIZE;
		numIndex--;

        // Convert frame to HSV color space
        Mat hsvFrame;
        Mat outputFrame;
        cvtColor(frame, hsvFrame, COLOR_BGR2HSV);

        // Threshold the HSV image to get only white colors
        Mat mask;
        inRange(hsvFrame, Scalar(0, 0, 200), Scalar(180, 55, 255), mask);

        // Find contours
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(mask, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

        // Copy the input frame to output frame to draw bounding boxes
        frame.copyTo(outputFrame);

        bool waterBottleDetected = false;
        for (size_t i = 0; i < contours.size(); i++) {
            Rect boundingRect = cv::boundingRect(contours[i]);
            double aspectRatio = (double)boundingRect.height / (double)boundingRect.width;

            // Simple heuristic for water bottle detection based on aspect ratio and size
            if (aspectRatio > 1.5 && boundingRect.height > 50 && boundingRect.width > 50) {
                rectangle(outputFrame, boundingRect, Scalar(255, 0, 0), 2);
                // Save the frame as an image file
                std::ostringstream filename;
                filename << "detect_" << j << ".png";
                imwrite(filename.str(), outputFrame);
                //printf("Bottle detected at iter %d\n",j); 
                //printf("width: %d\n", boundingRect.width);
                //printf("height: %d\n", boundingRect.height);
                //printf("\n");
                waterBottleDetected = true;
                j += 1;
                break;
            }
            else{
                std::ostringstream filename;
                filename << "frame_" << j << ".png";
                imwrite(filename.str(), outputFrame);
                j += 1;
            }

        }

		pthread_mutex_unlock (&m);
		pthread_cond_signal (&c_prod);
        
        //waterBottleDetected = std::rand() % 2;
        //printf("waterBottle: %d ", waterBottleDetected);
        
        /* Insert into flags buffer */
        pthread_mutex_lock (&f);
		if (numFlags > FLAG_BUF_SIZE) exit(1);	/* overflow */
		while (numFlags == FLAG_BUF_SIZE)			/* block if buffer is full */
			pthread_cond_wait (&f_prod, &f);
		/* if executing here, buffer not full so add element */
        if (waterBottleDetected){
            //printf("adding true %d\n", numTrue);
            numTrue += 1;
        }
        else{
            //printf("adding false\n");
        }
		flags[addFlagIndex] = waterBottleDetected;
		addFlagIndex = (addFlagIndex+1) % FLAG_BUF_SIZE;
		numFlags++;
		pthread_mutex_unlock (&f);
		pthread_cond_signal (&f_cons);
	//	printf ("Consumed frame\n");  fflush(stdout);       
    }

    printf("tracker thread returning\n");
    return nullptr;
}