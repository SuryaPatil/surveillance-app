/*
* This example demonstrates sending a SMS or MMS in C++ using the Twilio REST
* APIs.  After building, you should be able to run it with:
* 
* ./bin/cpp_demo
* 
*/

#include <iostream>
#include <string>
#include <memory>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "twilio.hpp"


int alert(int argc, char * argv[])
{
        int cmd;
        std::string account_sid;
        std::string auth_token;
        std::string message;
        std::string from_number;
        std::string to_number;
        std::string picture_url;
        bool verbose = false;

        for (int i = 0; i < argc; i++) {
                //printf("arg %d %s\n", i, argv[i]);
                if (i > 8) {
                if (!message.empty()) {
                        message += ' '; // Add a space before each new word except the first one
                }
                message += argv[i];
                }
        }

        std::cout << "Message: " << message << std::endl;
       // printf("1\n");
        opterr = 0;

        while ((cmd = getopt(argc, argv, "a:s:m:f:t:p:vh?")) != -1) {
                switch (cmd) {
                        case '?':
                        case 'h':
                                printf("Twilio C++ Example Help:\n");
                                printf("-a: Account\t\t"
                                       "(ex: -a \"ACXXXXX\")\n");
                                printf("-s: Auth Token\t\t"
                                       "(ex: -s \"your_token\")\n");
                                printf("-f: From Number\t\t"
                                       "(ex: -f \"+18005551212\")\n");
                                printf("-t: To Number\t\t"
                                       "(ex: -t \"+18005551212\")\n");
                                printf("-m: Message to send\t"
                                       "(ex: -m \"Hello, Twilio!\")\n");
                                printf("-p: (Opt.) URL to Image\t"
                                       "(ex: -p \"Hello, Twilio!\")\n");
                                printf("-v: Verbose Mode\n");
                                printf("-h: This help dialog\n");
                                return 0;
                        case 's':
                                auth_token = optarg;
                                break;
                        case 'f':
                                from_number = optarg;
                                break;
                        case 't':
                                to_number = optarg;
                                break;
                        case 'p':
                                picture_url = optarg;
                                break;
                        case 'v':
                                verbose = true;
                                break;
                        default:
                                continue;
                }
        }
        bool good = false;

        if ( account_sid.empty()) {
                printf("sid: %s\n", account_sid.c_str());
                std::cout<< "You didn't include account_sid\n" << std::endl;
                good = true;
        }
        if ( auth_token.empty()) {
                printf("auth_token: %s\n", auth_token.c_str());
                std::cout<< "You didn't include auth_token\n" << std::endl;
                good = true;
        }
        if ( from_number.empty()) {
                printf("from_number: %s\n", from_number.c_str());
                std::cout<< "You didn't include from_number\n" << std::endl;
                good = true;
        }
        if ( to_number.empty()) {
                printf("to_number: %s\n", to_number.c_str());
                std::cout<< "You didn't include to_number\n" << std::endl;
                good = true;
        }
        //printf("2\n");
        if ( message.empty()) {
                std::cout<< "You didn't include message\n" << std::endl;
                good = true;
        }
        if (good){
                printf("bye\n");
                return -1;
        }

        // if ( account_sid.empty() or auth_token.empty() or from_number.empty()
        //         or to_number.empty() or message.empty() ) {
        //         std::cout<< "You didn't include all necessary inputs!\n"
        //                 "Call using -h for help.\n" << std::endl;
        //         return -1;
        // }

        // Instantiate a twilio object and call send_message
        std::string response;
        auto twilio = std::make_shared<twilio::Twilio>(
            account_sid, 
            auth_token
        );
        printf("sending message...\n");
        bool message_success = twilio->send_message(
                to_number, 
                from_number, 
                message,
                response,
                picture_url,
                verbose
        );

        // Report success or failure
        if (!message_success) {
                if (verbose) {
                        std::cout << "Message send failed." << std::endl;
                        if (!response.empty()) {
                                std::cout << "Response:" << std::endl 
                                        << response << std::endl;
                        }
                }
                return -1;
        } else if (verbose) {
                std::cout << "SMS sent successfully!" << std::endl;
                std::cout << "Response:" << std::endl << response
                        << std::endl;
        }

        return 0;
}