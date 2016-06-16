//
// Created by Tom Wang on 16/5/29.
//

#include "ClientSocket.h"
#include "ExceptionSock.h"
#include "log.h"

ClientSocket::ClientSocket ( std::string host, int port )
{
    if ( ! Socket::create() )
    {
        throw ExceptionSock ( "Could not create client socket." );
    }

    if ( ! Socket::connect ( host, port ) )
    {
        throw ExceptionSock ( "Could not bind to port." );
    }

    //Socket::set_non_blocking(true);

}

void ClientSocket::conn ( std::string host, int port )
{
    if ( ! Socket::create() )
    {
        throw ExceptionSock ( "Could not create client socket." );
    }

    if ( ! Socket::connect ( host, port ) )
    {
        throw ExceptionSock ( "Could not bind to port." );
    }

    //Socket::set_non_blocking(true);

}



const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
{
    int i = 0;
    if ( ! Socket::send ( s ) )
    {
        throw ExceptionSock ( "Could not write to socket." );
    }
    usleep(25);
    return *this;

}


const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
    if ( ! Socket::recv ( s ) )
    {
        throw ExceptionSock ( "Could not read from socket." );
    }
    usleep(25);
    return *this;
}
