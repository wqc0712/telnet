//
// Created by Tom Wang on 16/5/29.
//

#include "ClientSocket.h"
#include "ExceptionSock.h"
#include <iostream>
#include <string>
#include <netdb.h>
#include <unistd.h>
#include <sstream>
#include <pthread.h>
#include "DefineType.h"
#include "configure.h"

using namespace std;

pthread_mutex_t pmutex;
pthread_t input;
pthread_t output;
bool GetCode = false;
bool stop =false;
void* inputthread(void* argc) {
    ClientSocket* clientsock = (ClientSocket*)argc;
    while (true) {
        string data;
        string reply;
        try {
            while (GetCode) {
                usleep(50);
            }
            pthread_mutex_lock(&pmutex);
            *clientsock >> data;
            if (IsConfigure(data)) {
                reply = DealConfigure(data);
                *clientsock << reply;
                pthread_mutex_unlock(&pmutex);
                usleep(20);
                continue;
            }
            cout << data;
            GetCode = true;
            if (stop) {
                break;
            }
            pthread_mutex_unlock(&pmutex);
            usleep(20);
        } catch (ExceptionSock) {

        }
    }
    return (void*)0;
}

void* outputthread(void* argc) {
    ClientSocket* clientsock = (ClientSocket*)argc;
    while (true) {
        string reply;
        try {
            while (!GetCode) {
                usleep(50);
            }
            cin >> reply;
            if (reply == "exit") {
                pthread_mutex_lock(&pmutex);
                *clientsock << reply;
                stop = true;
                delete clientsock;
                pthread_mutex_unlock(&pmutex);
                usleep(15);
                break;
            }
            pthread_mutex_lock(&pmutex);
            int i = 0;
            while (i < reply.length()) {
                string t = "";
                t = t + reply[i];
                *clientsock << t;
                i = i + 1;
            }
            string t = "";
            t = t + "\r\n";
            *clientsock << t;
            pthread_mutex_unlock(&pmutex);
            GetCode = false;
            usleep(15);
        } catch (ExceptionSock) {

        }
    }
    return (void*)0;
}

int main(){
    ClientSocket* clientsock = new ClientSocket("10.110.28.196",SERV_PORT);
    pthread_mutex_init(&pmutex,NULL);
    pthread_create(&output,NULL,outputthread,clientsock);
    pthread_create(&input,NULL,inputthread,clientsock);

    pthread_join(input,NULL);
    pthread_join(output,NULL);
    pthread_mutex_destroy(&pmutex);
    return 0;
}