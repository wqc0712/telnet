//
// Created by Tom Wang on 16/5/29.
//

#include "ServerSocket.h"
#include "ExceptionSock.h"
#include "DefineType.h"
#include <string>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <pthread.h>

using namespace std;

string ipTable[100];
string message[100];
string UserName = "User";
string Passwd = "Passwd";
bool used[100] = {false};
int id[100];


void* thread(void* argv) {
    ServerSocket* new_sock = (ServerSocket*)argv;

    try {
        while (true) {
            string data;
            string reply;
            *new_sock >> data;
            reply = data + "\n";
            if (data == "exit") {
                delete new_sock;
                return (void*)0;
            }
            *new_sock << reply;
            cout << new_sock->get_socket_ip() << "::" << data << endl;
        }
    } catch (ExceptionSock e) {
        cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
    return (void*)1;
}

int main(int argc, char* argv[]) {
    cout << "Telnet Server is running...\n";

    int num = -1;
    int n = 0;

    pthread_t tid[100];
    pthread_mutex_t mutex;

    for (int i = 0;i < 10;i++) {id[i] = i;message[i] = "";}
    try {
        ServerSocket server(SERV_PORT);
        ServerSocket* new_sock = new ServerSocket();
            cout << "Begin!" << endl;

            int i = 0;
            try {

                while (true) {
                    server.accept(*new_sock);
                    i = i + 1;
                    string data;
                    string reply;
                    reply = "Welcome To my Telnet Servers!\nPlease input your User Name!\nUser Name:";
                    *new_sock << reply;
                    *new_sock >> data;
                    if (data == UserName) {
                        reply = "Password:";
                        *new_sock << reply;
                        *new_sock >> data;
                        if (data == Passwd) {
                            reply = "Login success!\n";
                            *new_sock << reply;
                            n = n + 1;
                            int ret;
                            ret = pthread_create(&tid[n-1],NULL,thread,(void*)new_sock);
                            new_sock = new ServerSocket;
                            continue;
                        } else {
                            reply = "Wrong Password!\n";
                            *new_sock << reply;
                            delete new_sock;
                            new_sock = new ServerSocket();
                            continue;
                        }
                    } else {
                        reply = "Wrong User Name!\n";
                        *new_sock << reply;
                        delete new_sock;
                        new_sock = new ServerSocket();
                        continue;
                    }

                }
            } catch (ExceptionSock& e) {
                cout << "Exception was caught:" << e.description() << "\nExiting.\n";
            }
    } catch (ExceptionSock& e) {
        cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
}