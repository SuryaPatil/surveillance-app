#include <pthread.h>
#include "source.hpp"
#include<signal.h> 
#include "stdio.h"
#include "twilio.hpp"
#include <iterator>
#include <thread> // For sleep_for
#include <chrono> // For chrono::seconds

bool running = true; 

Mat buffer[BUF_SIZE]; // Define the buffer
int addIndex = 0;
int remIndex = 0;
int numIndex = 0;
pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_cons=PTHREAD_COND_INITIALIZER;
pthread_cond_t c_prod=PTHREAD_COND_INITIALIZER;

bool flags[FLAG_BUF_SIZE]; 
int addFlagIndex = 0;
int remFlagIndex = 0;
int numFlags = 0;
pthread_mutex_t f=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t f_cons=PTHREAD_COND_INITIALIZER;
pthread_cond_t f_prod=PTHREAD_COND_INITIALIZER;

// Ctrl-C at keyboard 
void handle_sigint(int sig) 
{ 
    printf("Caught signal %d\n", sig); 
    running = false;
} 

int main(){
    
    signal(SIGINT, handle_sigint); 

    pthread_t tid1, tid2, tid3;		/* thread identifiers */
	int i;

	/* create digitizer thread */
	if (pthread_create(&tid1,NULL,capture,NULL) != 0) {
		fprintf (stderr, "Unable to create digitizer thread\n");
		exit (1);
	}
    /* create tracker thread */
	if (pthread_create(&tid2,NULL,trackerFunction,NULL) != 0) {
		fprintf (stderr, "Unable to create tracker thread\n");
		exit (1);
	}
    /* create tracker thread */
	if (pthread_create(&tid3,NULL,alarm,NULL) != 0) {
		fprintf (stderr, "Unable to create alarm thread\n");
		exit (1);
	}
    // wait for created threads to exit
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    printf ("Parent quiting\n");

    return 0;
}