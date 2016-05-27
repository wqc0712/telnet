//
// Created by Tom Wang on 16/5/27.
//

#ifndef TELNET_SOCKET_H
#define TELNET_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>


#define MAXHOSTNAME 200//客户端名字最大长度
#define MAXCONNECTIONS 5//最大并发连接数
#define MAXRECV 500//最大接受长度

class Socket
{
public:
    Socket();
    virtual ~Socket();

    // 服务端初始化程序
    bool create();
    bool bind ( const int port );
    bool listen() const;
    bool accept ( Socket& ) const;

    // 客户端初始化程序
    bool connect ( const std::string host, const int port );

    // 数据传输函数
    bool send ( const std::string ) const;
    int recv ( std::string& ) const;


    void set_non_blocking ( const bool );

    bool is_valid() const { return m_sock != -1; }

private:

    int m_sock;
    sockaddr_in m_addr;


};

#endif //TELNET_SOCKET_H
