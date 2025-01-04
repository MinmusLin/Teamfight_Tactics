/****************************************************************
 * Project Name:  Server
 * File Name:     Server.h
 * File Function: Server类的定义
 * Author:        林继申
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _SERVER_H_
#define _SERVER_H_

#include <WinSock2.h>
#include <vector>
#include "../proj.win32/Constant.h"

/*
 * Class Name:     Server
 * Class Function: 服务器类
 */
class Server {
public:
    // 构造函数
    Server();

    // 析构函数
    ~Server();

    // 运行服务器
    void run();

    // 友元函数声明
    friend void clientHandler(const SOCKET clientSocket, Server& server);

private:
    WSADATA wsaData;                                        // Windows Sockets API
    SOCKET serverSocket, clientSocket;                      // 服务器和客户端的 socket
    struct sockaddr_in server, client;                      // 服务器和客户端的地址信息
    char hostname[HOSTNAME_MAX_LENGHT];                     // 主机名
    struct hostent* host;                                   // 主机地址
    int port;                                               // 端口
    int currentConnections;                                 // 服务器当前连接数量
    std::vector<SOCKET> clients;                            // 所有连接到服务器的客户端套接字
    std::vector<std::map<SOCKET, std::string>> playerNames; // 所有连接到服务器的客户端玩家昵称
    std::vector<std::map<SOCKET, std::string>> battleMaps;  // 所有连接到服务器的客户端玩家战斗区地图

    // 创建和尝试绑定套接字
    void createAndBindSocket();

    // 监听和接受客户端的连接请求并进行处理
    void handleConnections();

    // 检查所有连接到服务器的客户端信息均已发送
    bool areAllReady(const std::vector<std::map<SOCKET, std::string>>& data);

    // 关闭客户端套接字
    void closeClientSocket(const SOCKET clientSocket);

    // 序列化所有连接到服务器的客户端玩家昵称
    std::string serializePlayerNames();

    // 获取键值对数据
    std::string getPairedData(const std::vector<std::map<SOCKET, std::string>>& data, size_t index);

    // 清空所有连接到服务器的客户端玩家字符串数据
    void clearStrings(std::vector<std::map<SOCKET, std::string>>& data);
};

#endif // !_SERVER_H_
