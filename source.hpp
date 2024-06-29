#ifndef SOURCE_HPP
#define SOURCE_HPP
#define BUF_SIZE 3

#include "opencv2/opencv.hpp"
void *capture(void *param);
bool trackerFunction(const cv::Mat& frame, cv::Mat& outputFrame);


/* Size of shared buffer */
// extern int buffer[BUF_SIZE];							/* shared buffer */
// extern int add=0;										/* place to add next element */
// extern int rem=0;										/* place to remove next element */
// extern int num=0;										/* number elements in buffer */
// extern pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;	/* mutex lock for buffer */



#endif // SOURCE_HPP
