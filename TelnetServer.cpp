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
bool used[100] = {false};
int id[100];

int main(int argc, char* argv[]) {
    cout << "Telnet Server is running...\n";

    int num = -1;
    int n = 0;

    pthread_t tid[100];
    pthread_mutex_t mutex;

    for (int i = 0;i < 10;i++) {id[i] = i;message[i] = "";}
    try {
        ServerSocket server(SERV_PORT);
        while (true) {

        }
    } catch (ExceptionSock) {

    }
}