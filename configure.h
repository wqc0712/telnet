//
// Created by Tom Wang on 16/6/6.
//

#ifndef TELNET_CONFIGURE_H
#define TELNET_CONFIGURE_H

#include <string>
#include "DefineType.h"
#include <iostream>

bool IsConfigure(std::string data);
std::string DealConfigure(std::string data);
std::string SendConfigure();

std::string DealWill(char option);
std::string DealDo(char option);
std::string DealWont(char option);
std::string DealDont(char option);

#endif //TELNET_CONFIGURE_H
