//
// Created by Tom Wang on 16/5/29.
//

#ifndef TELNET_CLIENTSOCKET_H
#define TELNET_CLIENTSOCKET_H

#include "Socket.h"


class ClientSocket : private Socket
{
public:
    void conn(std::string host, int port);
    void disconn();
    ClientSocket ( std::string host, int port );
    virtual ~ClientSocket(){};

    const ClientSocket& operator << ( const std::string& ) const;
    const ClientSocket& operator >> ( std::string& ) const;

};


#endif //TELNET_CLIENTSOCKET_H
