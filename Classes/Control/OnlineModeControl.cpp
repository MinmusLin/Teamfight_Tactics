/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeControl.cpp
 * File Function: OnlineModeControl���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <cstring>
#include "OnlineModeControl.h"

// ����ǳ�
extern std::string g_PlayerName;

// ���캯��
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

// ��������
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

// �����ͻ���
ConnectionStatus OnlineModeControl::initializeClient()
{
    // ��ʼ�� Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Function WSAStartup failed with error: " << WSAGetLastError() << std::endl;
        return ConnectionError;
    }

    // �����׽���
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Function socket failed with error: " << WSAGetLastError() << std::endl;
        return ConnectionError;
    }

    // ���׽�������Ϊ������
    u_long mode = 1;
    if (ioctlsocket(s, FIONBIO, &mode) != NO_ERROR) {
        std::cerr << "Function ioctlsocket failed with error: " << WSAGetLastError() << std::endl;
        return ConnectionError;
    }

    // ׼�� sockaddr_in �ṹ
    server.sin_addr.s_addr = inet_addr(ipv4);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // ���ӵ�Զ�̷�����
    if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        // ��������Ƿ�ɹ�
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            std::cerr << "Function connect failed with error: " << WSAGetLastError() << std::endl;
            return ConnectionError;
        }

        // ʹ�� select ��������Ƿ�ɹ�
        fd_set writefds;
        FD_ZERO(&writefds);
        FD_SET(s, &writefds);

        // ���÷��������ӳ�ʱʱ��
        struct timeval timeout;
        timeout.tv_sec = CONNECTION_TIMEOUT_DURATION;
        timeout.tv_usec = 0;

        // ����׽����Ƿ��д�����Ƿ������ӣ�
        int selectResult = select(0, NULL, &writefds, NULL, &timeout);
        if (selectResult > 0) {
            if (FD_ISSET(s, &writefds)) {
                int optVal, optLen = sizeof(optVal);
                if (getsockopt(s, SOL_SOCKET, SO_ERROR, (char*)&optVal, &optLen) == 0 && optVal == 0) {
                    // ʹ�� select �ȴ����ݵ���
                    fd_set readfds;
                    FD_ZERO(&readfds);
                    FD_SET(s, &readfds);

                    // ���÷��������ӳ�ʱʱ��
                    timeout.tv_sec = CONNECTION_TIMEOUT_DURATION;
                    timeout.tv_usec = 0;

                    // �ȴ��׽��ֱ�Ϊ�ɶ�
                    selectResult = select(0, &readfds, NULL, NULL, &timeout);
                    if (selectResult > 0) {
                        if (FD_ISSET(s, &readfds)) {
                            memset(message, 0, sizeof(message));
                            recvSize = recv(s, message, BUFFER_SIZE, 0);
                            if (recvSize > 0) { // �����������Ӧ��Ϣ
                                message[recvSize] = '\0';
                                if (!strcmp(message, CONNECTION_ACCEPTED_MSG)) { // ���ӽ���
                                    return ConnectionAccepted;
                                }
                                if (!strcmp(message, CONNECTION_REFUSED_MSG)) { // ���Ӿܾ�
                                    return ConnectionRefused;
                                }
                                return ConnectionError; // ���Ӵ���
                            }
                            else if (recvSize == 0) { // ���ӹر�
                                return ConnectionError;
                            }
                            else { // ���� recv ����
                                std::cerr << "Function recv failed with error: " << WSAGetLastError() << std::endl;
                                return ConnectionError;
                            }
                        }
                    }
                    else if (selectResult == 0) { // ���ӳ�ʱ
                        return ConnectionTimeout;
                    }
                    else { // ���� select ����
                        std::cerr << "Function select failed with error: " << WSAGetLastError() << std::endl;
                        return ConnectionError;
                    }
                }
            }
        }
        else if (selectResult == 0) { // ���ӳ�ʱ
            return ConnectionTimeout;
        }
        else { // ���� select ����
            std::cerr << "Function select failed with error: " << WSAGetLastError() << std::endl;
            return ConnectionError;
        }
    }
    return ConnectionError; // ���Ӵ���
}

// ��ȡ�ͻ��˵� socket
SOCKET OnlineModeControl::getSocket() const
{
    return s;
}

// �ͻ����ڷ������� socket
SOCKET OnlineModeControl::getMySocket() const
{
    return mySocket;
}

// �������������Ϣ
int OnlineModeControl::sendMessage(const char* str, const int len)
{
    return send(s, str, len, 0);
}

// ���÷�������ǰ��������
void OnlineModeControl::setCurrentConnections(const int currentConnections)
{
    this->currentConnections = currentConnections;
}

// ��ȡ��������ǰ��������
int OnlineModeControl::getCurrentConnections() const
{
    return currentConnections;
}

// ��ȡ�������ָ��
HumanPlayer* OnlineModeControl::getEnemyPlayer() const
{
    return enemyPlayer;
}

// ���õ������ս������ͼ
void OnlineModeControl::setEnemyBattleMap(const ChampionCategory battleMap[][BATTLE_MAP_COLUMNS])
{
    enemyPlayer->setBattleMap(battleMap);
}

// ��ʼ����ս��
void OnlineModeControl::initializeBattle()
{
    // ��ȡս��Ӣ�۵�ͼ
    ChampionCategory(*myFlagMap)[BATTLE_MAP_COLUMNS];
    ChampionCategory(*enemyFlagMap)[BATTLE_MAP_COLUMNS];
    humanPlayer->getBattleMap(myFlagMap);
    enemyPlayer->getBattleMap(enemyFlagMap);

    // ������ս��
    try {
        battle = new Battle(myFlagMap, enemyFlagMap);
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        throw;
    }
}

// �����л��������ӵ��������Ŀͻ�������ǳ�
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

// ��ȡ�������ӵ��������Ŀͻ�������ǳ�
std::vector<std::map<SOCKET, std::string>> OnlineModeControl::getPlayerNames() const
{
    return playerNames;
}

// ��ȡ�������ӵ��������Ŀͻ�����ҷ���
std::vector<std::map<SOCKET, int>> OnlineModeControl::getPlayerHealthPoints() const
{
    return playerHealthPoints;
}

// ���л����ս������ͼ
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

// �����л����ս������ͼ
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

// ��ȡ�ͻ��� socket �ڷ�����������
int OnlineModeControl::getSocketIndex()
{
    for (size_t i = 0; i < playerNames.size(); ++i) {
        if (playerNames[i].find(mySocket) != playerNames[i].end()) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// ������������Ϣ�߳�
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

// �����������ֵ
void OnlineModeControl::updatePlayerHealthPoints(const int healthPoint, const SOCKET socket)
{
    std::lock_guard<std::mutex> lock(healthPointsMutex); // ����������ȷ���̰߳�ȫ��
    for (auto& playerMap : playerHealthPoints) {
        for (auto& pair : playerMap) {
            if (pair.first == socket) {
                pair.second = healthPoint;
                return;
            }
        }
    }
}