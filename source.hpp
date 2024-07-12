#ifndef SOURCE_HPP
#define SOURCE_HPP
#define BUF_SIZE 3
#define FLAG_BUF_SIZE 3

#include "opencv2/opencv.hpp"
using namespace cv;

void *capture(void *param);
void *trackerFunction(void *param);
void *alarm(void *param);

/* Size of shared buffer */
#define BUF_SIZE 3

extern bool running;    /* Set to false when all threads should stop running */

extern Mat buffer[BUF_SIZE];							/* shared buffer */
extern int addIndex;								    /* place to add next element */
extern int remIndex;								/* place to remove next element */
extern int numIndex;								/* number elements in buffer */
extern pthread_mutex_t m;	/* mutex lock for buffer */
extern pthread_cond_t c_cons; /* consumer waits on this cond var */
extern pthread_cond_t c_prod; /* producer waits on this cond var */

extern bool flags[FLAG_BUF_SIZE];							/* shared buffer */
extern int addFlagIndex;							    /* place to add next element */
extern int remFlagIndex;							/* place to remove next element */
extern int numFlags;							/* number flags in flags buffer */
extern pthread_mutex_t f;	/* mutex lock for flags buffer */
extern pthread_cond_t f_cons; /* consumer waits on this cond var */
extern pthread_cond_t f_prod; /* producer waits on this cond var */

#endif // SOURCE_HPP