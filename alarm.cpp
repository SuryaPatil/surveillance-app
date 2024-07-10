#include <vector>
#include "source.hpp"

using namespace std;

void *alarm(void *param) {
    int numMgs = 0;
    while(running) {

        pthread_mutex_lock (&f);
		if (numFlagIndex < 0) exit(1);   /* underflow */
		while (numFlagIndex == 0)		/* block if buffer empty */
			pthread_cond_wait (&f_cons, &f);
		/* if executing here, buffer not empty so remove element */
		bool i = flags[remFlagIndex];
		remFlagIndex = (remFlagIndex+1) % BUF_SIZE;
		numFlagIndex--;

        if (i){
            printf("Must send message %d\n", numMgs);
            numMgs += 1;
        }
		pthread_mutex_unlock (&f);
		pthread_cond_signal (&f_prod);

    }
    printf("alarm thread returning\n");
    return nullptr;
}