//
// Created by Tom Wang on 16/6/6.
//

#include "configure.h"

using namespace std;

bool IsConfigure(string data) {
    if ((uint8_t)data[0] == IAC) {
        return true;
    } else {
        return false;
    }
}

string DealConfigure(string data) {
    int i = 0;
    string result = "";
    string OP = "";
    while (i < data.length()) {
        if ((uint8_t)data[i] != IAC) {
            while (i < data.length()) {
                OP = OP + data[i];
                i = i + 1;
            }
            break;
        }
        i = i + 1;
        if ((uint8_t)data[i] == WILL) {
            i = i+ 1;
            result = result + DealWill(data[i]);
            i = i + 1;
            continue;
        }
        if ((uint8_t)data[i] == DO) {
            i = i + 1;
            result = result + DealDo(data[i]);
            i = i + 1;
            continue;
        }
        if ((uint8_t)data[i] == WONT) {
            i = i + 1;
            result = result + DealWont(data[i]);
            i = i + 1;
            continue;
        }
        if ((uint8_t)data[i] == DONT) {
            i = i + 1;
            result = result + DealDont(data[i]);
            i = i + 1;
            continue;
        }
    }
    if (OP.length() > 0) {
        cout << OP;
    }
    return result;
}

string SendConfigure();

string DealWill(char option){
    string result = "";
    result = result + (char)IAC;
    result = result + (char)DONT;
    result = result + option;
    return result;
}

string DealDo(char option){
    string result;
    result = result + (char)IAC;
    result = result + (char)WONT;
    result = result + option;
    return result;
}

string DealWont(char option){
    string result;
    result = result + (char)IAC;
    result = result + (char)DONT;
    result = result + option;
    return result;
}

string DealDont(char option){
    string result;
    result = result + (char)IAC;
    result = result + (char)WONT;
    result = result + option;
    return result;
}

