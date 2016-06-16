//
// Created by Tom Wang on 16/6/6.
//

#include "configure.h"
#include "log.h"

using namespace std;

bool IsConfigure(string data) {
    if ((uint8_t)data[0] == IAC) {
        return true;
    } else {
        return false;
    }
}
string Statue;

string GetType(char option) {
    switch ((uint8_t) option) {
        case ECHO :{
            return "ECHO";
        }
        case _EOF :{
            return "EOF";
        }
        case SUSP :{
            return "SUSP";
        }
        case ABORT :{
            return "ABORT";
        }
        case EOR :{
            return "EOR";
        }
        case NOP :{
            return "NOP";
        }
        case DM :{
            return "DM";
        }
        case BRK :{
            return "BRK";
        }
        case IP :{
            return "IP";
        }
        case GA :{
            return "GA";
        }
        case SB :{
            return "SB";
        }
        case WILL :{
            return "WILL";
        }
        case WONT :{
            return "WONT";
        }
        case DO :{
            return "DO";
        }
        case DONT :{
            return "DONT";
        }
        case IAC :{
            return "IAC";
        }
        default:
            return "UNKNOWN";
    }
}

string PrintConfigure(string data) {
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
        result = Statue +" IAC ";
        if ((uint8_t)data[i] == WILL) {
            i = i+ 1;
            result = result + "WILL ";
            result = result + GetType(data[i]);
            result = result + "\n";
            i = i + 1;
            PrintLog(result);
            continue;
        }
        if ((uint8_t)data[i] == DO) {
            i = i + 1;
            result = result + "DO ";
            result = result + GetType(data[i]);
            result = result + "\n";
            i = i + 1;
            PrintLog(result);
            continue;
        }
        if ((uint8_t)data[i] == WONT) {
            i = i + 1;
            result = result + "WONT ";
            result = result + GetType(data[i]);
            result = result + "\n";
            i = i + 1;
            PrintLog(result);
            continue;
        }
        if ((uint8_t)data[i] == DONT) {
            i = i + 1;
            result = result + "DONT ";
            result = result + GetType(data[i]);
            result = result + "\n";
            i = i + 1;
            PrintLog(result);
            continue;
        }
    }
    if (OP.length() > 0) {
        OP = Statue+ " " + OP + "\n";
        PrintLog(OP);
    }
    return result;
}

string DealConfigure(string data) {
    int i = 0;
    string result = "";
    string OP = "";
    Statue = "Receive";
    PrintConfigure(data);
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
    Statue = "Send";
    PrintConfigure(result);
    return result;
}

string SendConfigure();

string DealWill(char option){
    string result = "";
    result = result + (char)IAC;
    //if (option != (uint8_t)ECHO) {
        result = result + (char) DONT;
        result = result + option;
   // } else {
   //     result = result + (char) DO;
  //      result = result + option;
  //  }
    return result;
}

string DealDo(char option){
    string result;
    result = result + (char)IAC;
   // if (option != (uint8_t)ECHO) {
        result = result + (char) WONT;
        result = result + option;
  //  } else {
  //      result = result + (char) WILL;
  //      result = result + option;
 //   }
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

