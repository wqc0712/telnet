//
// Created by Tom Wang on 16/5/27.
//

#include "Socket.h"
#include "string.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>


Socket::Socket()
{
    m_sock = -1;
    memset ( &m_addr, 0, sizeof ( m_addr ) );
    //sockaddr_in 初始化

}

Socket::~Socket()
{
    if ( is_valid() )
        ::close ( m_sock ); //如果还保持一个连接,则需要释放连接.
}

bool Socket::create()
{
    m_sock = socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP ); //使用Linux内置的socket函数开始创建socket
    // AF_INET代表IPv4连接,具体含义参考socket.h
    // SOCK_STREAM表示为面向连接的数据包,用于TCP连接,UDP应使用SOCK_DGRAM
    // IPPROTO_TCP代表TCP协议,具体应查看in.h

    if ( ! is_valid() )
        return false; //创建失败返回错误


    // TIME_WAIT - argh
    int on = 1;
    if ( setsockopt ( m_sock, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
        //setsockopt用于设定套接字的层次,第二个参数为level,第三个参数为optname,这里打开允许重用地址
        return false;


    return true;

}



bool Socket::bind ( const int port )
{
    //进行端口binding操作.
    if ( ! is_valid() )
    {
        return false;
    }



    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons ( port );

    int bind_return = ::bind ( m_sock,
                               ( struct sockaddr * ) &m_addr,
                               sizeof ( m_addr ) );


    if ( bind_return == -1 )
    {
        return false;
    }

    return true;
}


bool Socket::listen() const
{

    //开始监听端口
    if ( ! is_valid() )
    {
        return false;
    }

    int listen_return = ::listen ( m_sock, MAXCONNECTIONS );


    if ( listen_return == -1 )
    {
        return false;
    }

    return true;
}


bool Socket::accept ( Socket& new_socket ) const
{
    //接受链接
    int addr_length = sizeof ( m_addr );
    new_socket.m_sock = ::accept ( m_sock, ( sockaddr * ) &m_addr, ( socklen_t * ) &addr_length );

    if ( new_socket.m_sock <= 0 )
        return false;
    else
        return true;
}


bool Socket::send ( const std::string s ) const
{
    //发送消息
    int status = ::send ( m_sock, s.c_str(), s.size(), SO_NOSIGPIPE );
    if ( status == -1 )
    {
        return false;
    }
    else
    {
        return true;
    }
}


int Socket::recv ( std::string& s ) const
{
    //接受消息
    char buf [ MAXRECV + 1 ];//缓冲区

    s = "";

    memset ( buf, 0, MAXRECV + 1 );

    int status = ::recv ( m_sock, buf, MAXRECV, 0 );

    if ( status == -1 )
    {
        std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
        return 0;
    }
    else if ( status == 0 )
    {
        return 0;
    }
    else
    {
        s = buf;
        return status;
    }
}



bool Socket::connect ( const std::string host, const int port )
{
    if ( ! is_valid() ) return false;

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons ( port );

    int status = inet_pton ( AF_INET, host.c_str(), &m_addr.sin_addr );//进行地址编码方式转换

    if ( errno == EAFNOSUPPORT ) return false;

    status = ::connect ( m_sock, ( sockaddr * ) &m_addr, sizeof ( m_addr ) );

    if ( status == 0 )
        return true;
    else
        return false;
}

void Socket::set_non_blocking ( const bool b )
{

    int opts;

    opts = fcntl ( m_sock,F_GETFL );

    if ( opts < 0 )
    {
        return;
    }

    if ( b )
        opts = ( opts | O_NONBLOCK );
    else
        opts = ( opts & ~O_NONBLOCK );

    fcntl ( m_sock,F_SETFL,opts );

}