/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeControl.cpp
 * File Function: OnlineModeControl类的实现
 * Author:        林继申
 * Update Date:   2023/12/28
 * License:       MIT License
 ****************************************************************/

#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <cstring>
#include "OnlineModeControl.h"

// 构造函数
OnlineModeControl::OnlineModeControl(std::string ipv4, std::string portStr) :
    port(std::stoi(portStr)),
    recvSize(0),
    currentConnections(0),
    Control(0) // TODO: Control(0) 初始化
{
    strcpy(this->message, "");
    strcpy(this->ipv4, ipv4.c_str());
    try {
        humanPlayer = new HumanPlayer(cocos2d::UserDefault::getInstance()->getStringForKey("PlayerName"));
        enemyPlayer = new HumanPlayer("");
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        if (humanPlayer) {
            delete humanPlayer;
        }
        if (enemyPlayer) {
            delete enemyPlayer;
        }
        throw;
    }
}

// 析构函数
OnlineModeControl::~OnlineModeControl()
{
    closesocket(s);
    WSACleanup();
    delete humanPlayer;
    delete enemyPlayer;
    if (battle) {
        delete battle;
    }
}

// 创建客户端
ConnectionStatus OnlineModeControl::initializeClient()
{
    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Function WSAStartup failed with error: " << WSAGetLastError() << std::endl;
        return ConnectionError;
    }

    // 创建套接字
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Function socket failed with error: " << WSAGetLastError() << std::endl;
        return ConnectionError;
    }

    // 将套接字设置为非阻塞
    u_long mode = 1;
    if (ioctlsocket(s, FIONBIO, &mode) != NO_ERROR) {
        std::cerr << "Function ioctlsocket failed with error: " << WSAGetLastError() << std::endl;
        return ConnectionError;
    }

    // 准备 sockaddr_in 结构
    server.sin_addr.s_addr = inet_addr(ipv4);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // 连接到远程服务器
    if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        // 检查连接是否成功
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            std::cerr << "Function connect failed with error: " << WSAGetLastError() << std::endl;
            return ConnectionError;
        }

        // 使用 select 检测连接是否成功
        fd_set writefds;
        FD_ZERO(&writefds);
        FD_SET(s, &writefds);

        // 设置服务器连接超时时间
        struct timeval timeout;
        timeout.tv_sec = CONNECTION_TIMEOUT_DURATION;
        timeout.tv_usec = 0;

        // 检测套接字是否可写（即是否已连接）
        int selectResult = select(0, NULL, &writefds, NULL, &timeout);
        if (selectResult > 0) {
            if (FD_ISSET(s, &writefds)) {
                int optVal, optLen = sizeof(optVal);
                if (getsockopt(s, SOL_SOCKET, SO_ERROR, (char*)&optVal, &optLen) == 0 && optVal == 0) {
                    // 使用 select 等待数据到达
                    fd_set readfds;
                    FD_ZERO(&readfds);
                    FD_SET(s, &readfds);

                    // 设置服务器连接超时时间
                    timeout.tv_sec = CONNECTION_TIMEOUT_DURATION;
                    timeout.tv_usec = 0;

                    // 等待套接字变为可读
                    selectResult = select(0, &readfds, NULL, NULL, &timeout);
                    if (selectResult > 0) {
                        if (FD_ISSET(s, &readfds)) {
                            memset(message, 0, sizeof(message));
                            recvSize = recv(s, message, BUFFER_SIZE, 0);
                            if (recvSize > 0) { // 处理服务器响应消息
                                message[recvSize] = '\0';
                                if (!strcmp(message, CONNECTION_ACCEPTED_MSG)) { // 连接接受
                                    return ConnectionAccepted;
                                }
                                if (!strcmp(message, CONNECTION_REFUSED_MSG)) { // 连接拒绝
                                    return ConnectionRefused;
                                }
                                return ConnectionError; // 连接错误
                            }
                            else if (recvSize == 0) { // 连接关闭
                                return ConnectionError;
                            }
                            else { // 函数 recv 出错
                                std::cerr << "Function recv failed with error: " << WSAGetLastError() << std::endl;
                                return ConnectionError;
                            }
                        }
                    }
                    else if (selectResult == 0) { // 连接超时
                        return ConnectionTimeout;
                    }
                    else { // 函数 select 出错
                        std::cerr << "Function select failed with error: " << WSAGetLastError() << std::endl;
                        return ConnectionError;
                    }
                }
            }
        }
        else if (selectResult == 0) { // 连接超时
            return ConnectionTimeout;
        }
        else { // 函数 select 出错
            std::cerr << "Function select failed with error: " << WSAGetLastError() << std::endl;
            return ConnectionError;
        }
    }
    return ConnectionError; // 连接错误
}

// 获取客户端的 socket
SOCKET OnlineModeControl::getSocket() const
{
    return s;
}

// 向服务器发送信息
int OnlineModeControl::sendMessage(const char* str, const int len)
{
    return send(s, str, len, 0);
}

// 设置服务器当前连接数量
void OnlineModeControl::setCurrentConnections(const int currentConnections)
{
    this->currentConnections = currentConnections;
}

// 获取服务器当前连接数量
int OnlineModeControl::getCurrentConnections() const
{
    return currentConnections;
}

// 获取敌人玩家指针
HumanPlayer* OnlineModeControl::getEnemyPlayer() const
{
    return enemyPlayer;
}

// 初始化对战类
void OnlineModeControl::initializeBattle()
{
    // 获取战斗英雄地图
    ChampionCategory(*myFlagMap)[BATTLE_MAP_COLUMNS];
    ChampionCategory(*enemyFlagMap)[BATTLE_MAP_COLUMNS];
    humanPlayer->getBattleMap(myFlagMap);
    enemyPlayer->getBattleMap(enemyFlagMap);

    // 创建对战类
    try {
        battle = new Battle(myFlagMap, enemyFlagMap);
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        throw;
    }
}