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
#include "log.h"

using namespace std;

string ProgType = "Client";

string InputString = "";
string SockString = "";
pthread_mutex_t pmutex,LOCK,InputLock;
pthread_t input;
pthread_t output;
pthread_t watchingdog,watchingdog2;
bool BoolInput = false;
bool GetCode = false;
bool stop =false;


void* inputthread(void* argc) {
    ClientSocket* clientsock = (ClientSocket*)argc;
   /* string s="";
    s = s + (char)IAC+(char) DONT+(char)ECHO;
    *clientsock << s;
    s = "";
    s = s + (char)IAC+(char) WONT+(char)ECHO;
    *clientsock << s;*/
    while (true) {
        string data;
        string reply;
        try {
            while (SockString == "") {
                usleep(30);
            }
            pthread_mutex_lock(&pmutex);
            pthread_mutex_lock(&LOCK);
            data = SockString;
            SockString = "";

            pthread_mutex_unlock(&LOCK);
            if (IsConfigure(data)) {
                reply = DealConfigure(data);
                *clientsock << reply;
                pthread_mutex_unlock(&pmutex);
                usleep(20);
                continue;
            }
            PrintLog("Receive "+data+"\n");
            /*char buff[255];
            sprintf(buff,"%s\n",data.c_str());
            char temp[255];
            int i=0,j=0;
            for (i = 0;i < strlen(buff)-1;i++) {
                if (buff[i] == '\r') continue;
                temp[j] = buff[i];
                j++;
            }
            temp[j] = '\0';
            printf("%s",temp);*/
            pthread_mutex_lock(&InputLock);
            flush(cout);
            printf("%s",data.c_str());
            flush(cout);
            pthread_mutex_unlock(&InputLock);
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

void * waitforinput(void* argc) {
    while (1) {
        while (InputString != "" || !GetCode) usleep(5);
        getline(cin,InputString);
        if (InputString == "exit") return (void*) 0;
    }
}

void * waitforrece(void* argc) {
    ClientSocket* clientsock = (ClientSocket*)argc;
    string temp;
    while (1) {

        *clientsock >> temp;
        pthread_mutex_lock(&LOCK);
        SockString+=temp;
        pthread_mutex_unlock(&LOCK);
        if (InputString == "exit") return (void*) 0;
    }
}

void* outputthread(void* argc) {
    ClientSocket* clientsock = (ClientSocket*)argc;
    while (true) {
        string reply;
        try {
           // cin >> reply;
            while (!GetCode || InputString == "") {
                usleep(50);
            }
            reply = InputString;
            InputString = "";
            if (reply == "exit") {
                pthread_mutex_lock(&pmutex);
                reply = reply + "\r\n";
                PrintLog("Send  "+reply);
                try {
                    *clientsock << reply;
                } catch (ExceptionSock Err) {

                }
                stop = true;
                delete clientsock;
                pthread_mutex_unlock(&pmutex);
                CloseLog();
                usleep(15);
                break;
            }
            pthread_mutex_lock(&pmutex);
            int i = 0;
            string t = "";
            while (i < reply.length()) {
                t = t + reply[i];
                i = i + 1;
            }
            t = t + "\r\n";
            PrintLog("Send "+t);
            *clientsock << t;
            pthread_mutex_unlock(&pmutex);
            GetCode = false;
            usleep(15);
        } catch (ExceptionSock) {

        }
    }
    return (void*)0;
}

int main(int argc,char* argv[]){
    string ip = argv[1];
    system("stty -echo");
    try {
        ClientSocket *clientsock = new ClientSocket(ip, SERV_PORT);
        pthread_mutex_init(&pmutex, NULL);
        pthread_mutex_init(&LOCK, NULL);
        pthread_mutex_init(&InputLock, NULL);
        pthread_create(&output, NULL, outputthread, clientsock);
        pthread_create(&input, NULL, inputthread, clientsock);
        pthread_create(&watchingdog, NULL, waitforinput, NULL);
        pthread_create(&watchingdog2, NULL, waitforrece, clientsock);
        pthread_join(input, NULL);
        pthread_join(output, NULL);
        pthread_join(watchingdog, NULL);
        pthread_join(watchingdog2, NULL);
        pthread_mutex_destroy(&pmutex);
    }catch (ExceptionSock Err) {
        cerr << Err.description();
        CloseLog();
    }
    return 0;
}