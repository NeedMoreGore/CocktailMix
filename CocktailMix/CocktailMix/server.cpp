#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#include <wiringPi.h>
//#include <sys/types.h>
//#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include <unistd.h>
//#include <iostream>

#define PORT 55655
#define BACKLOG 10

using std::cout;
using std::endl;

int main() {
        cout << "cocktailmachine driver written in c++ using wiringpi library by Julian Metza" << endl;
//init gpio
        if (wiringPiSetup() == -1) {
                cout << "initialization of wiringpi library failed" << endl;
                return 1;
        }
        cout << "initialization of wiringpi library succeded" << endl;
//init pins
        int pinst[6];
        for (unsigned int i = 0; i < 6; i++) {
                pinMode(i, OUTPUT);
                digitalWrite(i, 0);
                pinst[i] = 0;
        }
        cout << "initialization of pin 11, 12, 13, 15, 16 and 18 succeded" << endl;
//networking part
try {
//init network
        int ssocket = socket(AF_INET, SOCK_STREAM, 0);
        if (ssocket == -1) {
                cout << "initialization of socket failed" << endl;
                return 1;
        }
        struct sockaddr_in saddr;
        memset(&saddr, 0, sizeof(saddr));
        saddr.sin_family = AF_INET;
        saddr.sin_addr.s_addr = INADDR_ANY;
        saddr.sin_port = htons(PORT);
        if (bind(ssocket, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
                cout << "could not bind socket" << endl;
                return 1;
        }
        cout << "initialization of socket succeded" << endl;
        if (listen(ssocket, BACKLOG) < 0) {
                cout << "setting listenmode failed" << endl;
                return 1;
        }
        cout << "server now listening for clients" << endl;

        struct sockaddr_in caddr;
        memset(&caddr, 0, sizeof(caddr));
        unsigned int caddrlen = sizeof(caddr);
        bool keepgoing = true;
        while (keepgoing) {
                int csocket = accept(ssocket, (struct sockaddr *) &caddr, &caddrlen);
                if (csocket < 0) {
                        cout << "accepting client failed" << endl;
                }
                cout << "accepting client succeded" << endl;

                char rbuffer[8];
                char wbuffer[8];
                do {
                        memset(&rbuffer, 0, sizeof(rbuffer));
                        memset(&wbuffer, 0, sizeof(wbuffer));
                        int n = read(csocket, rbuffer, sizeof(rbuffer));
                        if (n > 0) {
                                switch (rbuffer[0]) {
                                        case 's': //set <pinnr> <value>
                                                {
                                                int pinvl = rbuffer[6] - '0';
                                                rbuffer[0] = 'x';
                                                if (pinvl == 0 || pinvl == 1) {
                                                        if (rbuffer[4] == '*') {
                                                                for (unsigned int i = 0; i < 6; i++) {
                                                                        pinMode(i, OUTPUT);
                                                                        digitalWrite(i, pinvl);
                                                                        pinst[i] = 0;
                                                                }
                                                                cout << "set * = " << pinvl << endl;
                                                                wbuffer[0] = '0' + pinvl;
                                                        } else if (rbuffer[4] >= '0' && rbuffer[4] <= '5') {
                                                                int pinnr = rbuffer[4] - '0';
                                                                digitalWrite(pinnr, pinvl);
                                                                pinst[pinnr] = pinvl;
                                                                cout << "set " << pinnr << " = " << pinvl << endl;
                                                                wbuffer[0] = '0' + pinst[pinnr];
                                                        }
                                                }
                                                }
                                                break;
                                        case 'g': //get <pinnr>
                                                {
                                                int pinnr = rbuffer[4] -'0';
                                                cout << "get " << pinnr << " = " << pinst[pinnr] << endl;
                                                wbuffer[0] = '0' + pinst[pinnr];
                                                }
                                                break;
                                        case '!': //get <pinnr>
                                                keepgoing = false;
                                                break;
                                }
                                //write answer
                                write(csocket, wbuffer, sizeof(wbuffer));
                        } else {
                                rbuffer[0] = 'q';
                        }
                } while (rbuffer[0] != 'q' && rbuffer[0] != '!');
                cout << "cleanup after client disconnected" << endl;
                close(csocket);
                for (unsigned int i = 0; i < 6; i++) {
                        pinMode(i, OUTPUT);
                        digitalWrite(i, 0);
                        pinst[i] = 0;
                }
                cout << "gpio reset succeeded" << endl;
        }
        close(ssocket);
} catch (...) {
        cout << "serious error occurred trying to shutdown gracefully" << endl;
}
        for (unsigned int i = 0; i < 6; i++) {
                pinMode(i, OUTPUT);
                digitalWrite(i, 0);
                pinst[i] = 0;
        }
        cout << "gpio safety reset before graceful shutdown" << endl;

        cout << "shutting down server" << endl;
}