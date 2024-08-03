#include <vector>
#include "source.hpp"
#include <iterator>
#include <ctime>

using namespace std;

std::string getCurrentTimeString() {
    // Get current time
    std::time_t currentTime = std::time(nullptr);

    // Convert to local time
    char timeString[100];
    if (std::strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTime))) {
        return std::string(timeString);
    }

    return "";
}

void *alarm(void *param) {
    int numMgs = 0;


	// Argument string
    std::string missing_args = "-a " + account_sid + " -s " + auth_token + " -t \"+19784895418\" -f \"+18662615101\" -m Water bottle missing!";
    std::string return_args = "-a " + account_sid + " -s " + auth_token + " -t \"+19784895418\" -f \"+18662615101\" -m Water bottle returned!";

    std::string currentTime = getCurrentTimeString();

    missing_args += currentTime;
    return_args += currentTime;

    int missing = 0;
    int iter = 0;
    while(running) {

        pthread_mutex_lock (&f);
		if (numFlags < 0) exit(1);   /* underflow */
		while (numFlags == 0)		/* block if buffer empty */
			pthread_cond_wait (&f_cons, &f);
		/* if executing here, buffer not empty so remove element */
		bool i = flags[remFlagIndex];
		remFlagIndex = (remFlagIndex+1) % FLAG_BUF_SIZE;
		numFlags--;

        if (i == 0 && missing == 0 && iter > 10){
            printf("i: %d\n", i);
            printf("**WB MISSING! %d**\n", numMgs);

             // Split the string into individual arguments
            std::istringstream iss(missing_args);
            std::vector<std::string> tokens(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
            int argc = tokens.size();
            std::vector<char*> argv(argc);
            for (int i = 0; i < argc; ++i) {
                argv[i] = &tokens[i][0];
            }
            if (numMgs < 10){
            
                // Call the alert function
                int *r = alert(argc, argv.data());
                if (r != 0){
                    printf("error sending message\n");
                }
                else{
                    printf("successfully send message\n");
                }
            }
            numMgs += 1;
            missing = 1;
        }
        else if (i == 1 && missing == 1){
            printf("**WB RETURNED! %d**\n", numMgs);
            // Split the string into individual arguments
            std::istringstream iss(return_args);
            std::vector<std::string> tokens(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
            int argc = tokens.size();
            std::vector<char*> argv(argc);
            for (int i = 0; i < argc; ++i) {
                argv[i] = &tokens[i][0];
            }
            if (numMgs < 10){
            
                // Call the alert function
                int *r = alert(argc, argv.data());
                if (r != 0){
                    printf("error sending message\n");
                }
                else{
                    printf("successfully send message\n");
                }
            }
            numMgs += 1;
            
            missing = 0;
        }
        iter += 1;
		pthread_mutex_unlock (&f);
		pthread_cond_signal (&f_prod);

    }
    printf("alarm thread returning\n");
    return nullptr;
}