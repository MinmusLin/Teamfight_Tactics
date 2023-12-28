/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeControl.h
 * File Function: OnlineModeControl类的定义
 * Author:        林继申
 * Update Date:   2023/12/28
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _ONLINE_MODE_CONTROL_H_
#define _ONLINE_MODE_CONTROL_H_

#include <vector>
#include "Control.h"

/*
 * Class Name:     OnlineModeControl
 * Class Function: 联机模式游戏控制类
 */
class OnlineModeControl : public Control {
public:
    // 构造函数
    OnlineModeControl(std::string ipv4, std::string portStr);

    // 析构函数
    ~OnlineModeControl();

    // 创建客户端
    ConnectionStatus initializeClient();

    // 获取客户端的 socket
    SOCKET getSocket() const;

    // 向服务器发送信息
    int sendMessage(const char* str, const int len);

    // 设置服务器当前连接数量
    void setCurrentConnections(const int currentConnections);

    // 获取服务器当前连接数量
    int getCurrentConnections() const;

    // 获取敌人玩家指针
    HumanPlayer* getEnemyPlayer() const;

    // 初始化对战类
    void initializeBattle();

    // 反序列化所有连接到服务器的客户端玩家昵称
    void deserializePlayerNames(const std::string& data);

    // 获取所有连接到服务器的客户端玩家昵称
    std::vector<std::map<SOCKET, std::string>> getPlayerNames() const;

    // 获取所有连接到服务器的客户端玩家分数
    std::vector<std::map<SOCKET, int>> getPlayerHealthPoints() const;

private:
    char ipv4[IPV4_ADDRESS_MAX_LENGTH + 1];                 // IPv4 地址
    int port;                                               // 端口
    WSADATA wsaData;                                        // Windows Sockets API
    SOCKET s;                                               // 客户端的 socket
    struct sockaddr_in server;                              // 服务器地址信息
    char message[BUFFER_SIZE];                              // 数据缓冲区
    int recvSize;                                           // 接收数据大小
    int currentConnections;                                 // 服务器当前连接数量
    HumanPlayer* enemyPlayer;                               // 敌人玩家
    std::vector<std::map<SOCKET, std::string>> playerNames; // 所有连接到服务器的客户端玩家昵称
    std::vector<std::map<SOCKET, int>> playerHealthPoints;  // 所有连接到服务器的客户端玩家分数
};

#endif // !_ONLINE_MODE_CONTROL_H_