#include <pthread.h>
#include "source.hpp"

Mat buffer[BUF_SIZE]; // Define the buffer
int addIndex = 0;
int remIndex = 0;
int numIndex = 0;
pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_cons=PTHREAD_COND_INITIALIZER;
pthread_cond_t c_prod=PTHREAD_COND_INITIALIZER;

int main(){

    pthread_t tid1, tid2;		/* thread identifiers */
	int i;

    printf("addIndex: %d\n", addIndex);

	/* create digitizer thread */
	if (pthread_create(&tid1,NULL,capture,NULL) != 0) {
		fprintf (stderr, "Unable to create producer thread\n");
		exit (1);
	}
    /* create digitizer thread */
	if (pthread_create(&tid2,NULL,trackerFunction,NULL) != 0) {
		fprintf (stderr, "Unable to create producer thread\n");
		exit (1);
	}
    /* wait for created thread to exit */
	pthread_join(tid1,NULL);
    printf ("Parent quiting\n");

    return 0;
}