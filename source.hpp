#ifndef SOURCE_HPP
#define SOURCE_HPP
#define BUF_SIZE 3

#include "opencv2/opencv.hpp"
using namespace cv;

void *capture(void *param);
void *trackerFunction(void *param);


/* Size of shared buffer */
#define BUF_SIZE 3

extern Mat buffer[BUF_SIZE];							/* shared buffer */
extern int addIndex;										    /* place to add next element */
extern int remIndex;										/* place to remove next element */
extern int numIndex;										/* number elements in buffer */
extern pthread_mutex_t m;	/* mutex lock for buffer */
extern pthread_cond_t c_cons; /* consumer waits on this cond var */
extern pthread_cond_t c_prod; /* producer waits on this cond var */

#endif // SOURCE_HPP