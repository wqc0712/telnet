//
// Created by Tom Wang on 16/5/29.
//

#include "ClientSocket.h"
#include "ExceptionSock.h"

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

}



const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
{
    if ( ! Socket::send ( s ) )
    {
        throw ExceptionSock ( "Could not write to socket." );
    }
    usleep(3000);
    return *this;

}


const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
    if ( ! Socket::recv ( s ) )
    {
        throw ExceptionSock ( "Could not read from socket." );
    }
    usleep(3000);
    return *this;
}
