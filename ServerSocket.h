//
// Created by Tom Wang on 16/5/27.
// 这个程序用于Server的中间层,用于建立一个ServerSocket对象
//

#ifndef TELNET_SERVERSOCKET_H
#define TELNET_SERVERSOCKET_H



#include "Socket.h"

class ServerSocket : private Socket
{
public:

    ServerSocket ( int port );
    ServerSocket (){};
    virtual ~ServerSocket();

    const ServerSocket& operator << ( const std::string& ) const;
    const ServerSocket& operator >> ( std::string& ) const;

    void accept ( ServerSocket& );

    char* get_socket_ip();

};

#endif //TELNET_SERVERSOCKET_H
