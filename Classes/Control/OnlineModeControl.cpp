/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeControl.cpp
 * File Function: OnlineModeControl类的实现
 * Author:        林继申
 * Update Date:   2023/12/26
 ****************************************************************/

#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <cstring>
#include "OnlineModeControl.h"

// 构造函数
OnlineModeControl::OnlineModeControl(std::string ipv4, std::string portStr) :
    port(std::stoi(portStr)),
    Control(0)
{
    strcpy(this->ipv4, ipv4.c_str());
}

// 析构函数
OnlineModeControl::~OnlineModeControl()
{
    closesocket(s);
    WSACleanup();
}

// 创建客户端
ConnectionStatus OnlineModeControl::initializeClient()
{
    // 初始化 Winsock
    //     WSAStartup 用于启动 Windows Sockets API
    //     MAKEWORD(2,2) 指定请求 2.2 版本的 Winsock
    //     如果初始化失败，输出错误信息并返回 ConnectioError
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Function WSAStartup failed with error: " << WSAGetLastError() << std::endl;
        return ConnectionError;
    }

    // 创建套接字
    //     AF_INET 表示 IPv4 地址族
    //     SOCK_STREAM 表示提供顺序、可靠、基于连接的字节流
    //     如果套接字创建失败，输出错误信息并返回 ConnectioError
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Function socket failed with error: " << WSAGetLastError() << std::endl;
        return ConnectionError;
    }

    // 准备 sockaddr_in 结构
    //     inet_addr 转换 IPv4 地址从文本到二进制形式
    //     htons 转换端口号为 TCP/IP 网络字节顺序
    server.sin_addr.s_addr = inet_addr(ipv4);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // 连接到远程服务器
    //     connect 函数建立与指定套接字的连接
    //     如果连接失败，输出错误信息并返回 ConnectioError
    if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Function connect failed with error: " << WSAGetLastError() << std::endl;
        return ConnectionError;
    }

    // 接收来自服务器的数据
    //     recv 函数从套接字接收数据
    //     如果接收失败，输出错误信息并返回 ConnectioError
    if ((recvSize = recv(s, message, 1024, 0)) == SOCKET_ERROR) {
        std::cerr << "Function recv failed with error: " << WSAGetLastError() << std::endl;
        return ConnectionError;
    }

    // 处理服务器的响应消息
    //     如果服务器接受连接，返回 ConnectioAccepted
    //     如果服务器拒绝连接（服务器已满），返回 ConnectioRefused
    if (!strcmp(message, CONNECTION_ACCEPTED_MSG)) {
        return ConnectionAccepted;
    }
    if (!strcmp(message, CONNECTION_REFUSED_MSG)) {
        return ConnectionRefused;
    }
    return ConnectionError;
}