#include "tracker.hpp"
#include <vector>
#include "source.hpp"

using namespace cv;
using namespace std;

void *trackerFunction(void *param) {
    int j = 0;
    while (1){
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

        for (size_t i = 0; i < contours.size(); i++) {
            Rect boundingRect = cv::boundingRect(contours[i]);
            double aspectRatio = (double)boundingRect.height / (double)boundingRect.width;

            // Simple heuristic for water bottle detection based on aspect ratio and size
            if (aspectRatio > 1.5 && boundingRect.height > 50 && boundingRect.width > 50) {
                rectangle(outputFrame, boundingRect, Scalar(255, 0, 0), 2);
                // Save the frame as an image file
                std::ostringstream filename;
                filename << "frame_" << j << ".png";
                imwrite(filename.str(), outputFrame);
                printf("Bottle detected at iter %d\n",j); 
                printf("width: %d\n", boundingRect.width);
                printf("height: %d\n", boundingRect.height);
                // printf("aspect ratio: %f\n\n", aspectRatio);
                printf("\n");
            }
            else{
             //   printf("&No Bottle detected at iter %d\n", j);
            }

        }

        j += 1;
		pthread_mutex_unlock (&m);
		pthread_cond_signal (&c_prod);
	//	printf ("Consumed frame\n");  fflush(stdout);
        

    }
}