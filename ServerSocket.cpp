//
// Created by Tom Wang on 16/5/27.
//

#include "ServerSocket.h"
#include "ExceptionSock.h"
#include <iostream>

ServerSocket::ServerSocket ( int port )
{
    if ( ! Socket::create() )
    {
        throw ExceptionSock ( "Could not create server socket." );
    }

    if ( ! Socket::bind ( port ) )
    {
        throw ExceptionSock ( "Could not bind to port." );
    }

    if ( ! Socket::listen() )
    {
        throw ExceptionSock ( "Could not listen to socket." );
    }

}

ServerSocket::~ServerSocket()
{
}

//重定义输入输出,操作较为方便.
const ServerSocket& ServerSocket::operator << ( const std::string& s ) const
{
    if ( ! Socket::send ( s ) )
    {
        throw ExceptionSock ( "Could not write to socket." );
    }
    usleep(3000);
    return *this;

}


const ServerSocket& ServerSocket::operator >> ( std::string& s ) const
{
    if ( ! Socket::recv ( s ) )
    {
        throw ExceptionSock ( "Could not read from socket." );
    }
    usleep(3000);
//    std::cout << "Successful receive!" << std::endl;
    return *this;
}

void ServerSocket::accept ( ServerSocket& sock )
{
    if ( ! Socket::accept ( sock ) )
    {
        throw ExceptionSock ( "Could not accept socket." );
    }
}


char* ServerSocket::get_socket_ip(){
    return Socket::get_socket_ip();
}