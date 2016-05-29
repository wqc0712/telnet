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

using namespace std;

int main(){
    ClientSocket* clientsock = new ClientSocket("127.0.0.1",SERV_PORT);
    while (true) {
        string data;
        cin >> data;
        if (data == "exit") {
            break;
        }
        try {
            *clientsock << data;
        } catch (ExceptionSock) {

        }
    }
    return 0;
}