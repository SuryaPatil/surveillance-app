#include <pthread.h>

/* Size of shared buffer */
#define BUF_SIZE 3

extern int buffer[BUF_SIZE];							/* shared buffer */
extern int add=0;										/* place to add next element */
extern int rem=0;										/* place to remove next element */
extern int num=0;										/* number elements in buffer */
extern pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;	/* mutex lock for buffer */