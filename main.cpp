#include <pthread.h>
#include "source.hpp"

int main(){

    pthread_t tid1, tid2;		/* thread identifiers */
	int i;

	/* create the threads; may be any number, in general */
	if (pthread_create(&tid1,NULL,capture,NULL) != 0) {
		fprintf (stderr, "Unable to create producer thread\n");
		exit (1);
	}
    /* wait for created thread to exit */
	pthread_join(tid1,NULL);
    printf ("Parent quiting\n");

    return 0;
}