/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeControl.cpp
 * File Function: OnlineModeControl类的实现
 * Author:        林继申
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <cstring>
#include "OnlineModeControl.h"

// 玩家昵称
extern std::string g_PlayerName;

// 构造函数
OnlineModeControl::OnlineModeControl(std::string ipv4, std::string portStr) :
    port(std::stoi(portStr)),
    recvSize(0),
    currentConnections(0),
    keepListening(true),
    Control(MAX_CONNECTIONS)
{
    strcpy(this->message, "");
    strcpy(this->ipv4, ipv4.c_str());
    try {
        humanPlayer = new HumanPlayer(g_PlayerName);
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
    listeningThread = std::thread(&OnlineModeControl::listenForServerMessages, this);
}

// 析构函数
OnlineModeControl::~OnlineModeControl()
{
    keepListening = false;
    if (listeningThread.joinable()) {
        listeningThread.join();
    }
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

// 客户端在服务器的 socket
SOCKET OnlineModeControl::getMySocket() const
{
    return mySocket;
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

// 设置敌人玩家战斗区地图
void OnlineModeControl::setEnemyBattleMap(const ChampionCategory battleMap[][BATTLE_MAP_COLUMNS])
{
    enemyPlayer->setBattleMap(battleMap);
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

// 反序列化所有连接到服务器的客户端玩家昵称
void OnlineModeControl::deserializePlayerNames(const std::string& data)
{
    if (data.substr(0, strlen(START_GAME_MSG)) == static_cast<std::string>(START_GAME_MSG)) {
        std::string newData = data.substr(strlen(START_GAME_MSG));
        std::istringstream ss(newData);
        std::string mapStr;
        while (std::getline(ss, mapStr, ';')) {
            if (!mapStr.empty()) {
                std::istringstream mapStream(mapStr);
                std::string pairStr;
                std::map<SOCKET, std::string> map;
                SOCKET key;
                while (std::getline(mapStream, pairStr, ',')) {
                    auto separatorPos = pairStr.find(':');
                    if (separatorPos != std::string::npos) {
                        key = std::stol(pairStr.substr(0, separatorPos));
                        std::string value = pairStr.substr(separatorPos + 1);
                        map[key] = value;
                    }
                }
                if (!map.empty()) {
                    playerNames.push_back(map);
                    playerHealthPoints.push_back({ { key, INITIAL_HEALTH_POINTS } });
                    if (map[key] == g_PlayerName) {
                        mySocket = key;
                    }
                }
            }
        }
    }
}

// 获取所有连接到服务器的客户端玩家昵称
std::vector<std::map<SOCKET, std::string>> OnlineModeControl::getPlayerNames() const
{
    return playerNames;
}

// 获取所有连接到服务器的客户端玩家分数
std::vector<std::map<SOCKET, int>> OnlineModeControl::getPlayerHealthPoints() const
{
    return playerHealthPoints;
}

// 序列化玩家战斗区地图
std::string OnlineModeControl::serializePlayerMap()
{
    std::string serializedMap = "";
    ChampionCategory(*championMap)[BATTLE_MAP_COLUMNS];
    humanPlayer->getBattleMap(championMap);
    for (int row = 0; row < PLACE_MAP_ROWS; ++row) {
        for (int col = 0; col < BATTLE_MAP_COLUMNS; ++col) {
            if (championMap[row][col] == NoChampion) {
                serializedMap += '0';
            }
            else {
                serializedMap += static_cast<char>(championMap[row][col] + 'A' - 1);
            }
        }
    }
    return serializedMap;
}

// 反序列化玩家战斗区地图
void OnlineModeControl::deserializeBattleMap(const std::string battleMapData, ChampionCategory battleMap[][BATTLE_MAP_COLUMNS])
{
    int index = 0;
    for (int row = 0; row < PLACE_MAP_ROWS; ++row) {
        for (int col = 0; col < BATTLE_MAP_COLUMNS; ++col) {
            char ch = battleMapData[index++];
            if (ch == '0') {
                battleMap[row][col] = NoChampion;
            }
            else {
                battleMap[row][col] = static_cast<ChampionCategory>(ch - 'A' + 1);
            }
        }
    }
}

// 获取客户端 socket 在服务器的索引
int OnlineModeControl::getSocketIndex()
{
    for (size_t i = 0; i < playerNames.size(); ++i) {
        if (playerNames[i].find(mySocket) != playerNames[i].end()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// 监听服务器消息线程
void OnlineModeControl::listenForServerMessages()
{
    while (keepListening) {
        char buffer[BUFFER_SIZE];
        recv(s, buffer, BUFFER_SIZE, 0);
        if (!strncmp(buffer, HEALTH_POINTS_IDENTIFIER, MESSAGE_IDENTIFIER_LENGTH)) {
            int healthPoints;
            SOCKET socket;
            sscanf(buffer, HEALTH_POINTS_FORMAT, &healthPoints, &socket);
            updatePlayerHealthPoints(healthPoints, socket);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_SLEEP_DURATION_MILLISECONDS));
    }
}

// 更新玩家生命值
void OnlineModeControl::updatePlayerHealthPoints(const int healthPoint, const SOCKET socket)
{
    std::lock_guard<std::mutex> lock(healthPointsMutex); // 锁定互斥量确保线程安全性
    for (auto& playerMap : playerHealthPoints) {
        for (auto& pair : playerMap) {
            if (pair.first == socket) {
                pair.second = healthPoint;
                return;
            }
        }
    }
}