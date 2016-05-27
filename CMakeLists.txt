cmake_minimum_required(VERSION 3.3)
project(telnet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SERVER_SOURCE Socket.cpp ServerSocket.cpp ExceptionSock.cpp)
set(CLIENT_SOURCE Socket.cpp ServerSocket.cpp ExceptionSock.cpp)
add_executable(server ${SERVER_SOURCE})
add_executable(client ${CLIENT_SOURCE})