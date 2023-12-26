/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeControl.h
 * File Function: OnlineModeControl��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/26
 ****************************************************************/

#pragma once
#ifndef _ONLINE_MODE_CONTROL_H_
#define _ONLINE_MODE_CONTROL_H_

#include <vector>
#include "Control.h"
#include "Player/HumanPlayer.h"
#include "Battle/Battle.h"

/*
 * Class Name:     OnlineModeControl
 * Class Function: ����ģʽ��Ϸ������
 */
class OnlineModeControl : public Control {
public:
    // ���캯��
    OnlineModeControl(std::string ipv4, std::string portStr);

    // ��������
    ~OnlineModeControl();

    // �����ͻ���
    ConnectionStatus initializeClient();

    // ��ȡ�ͻ��˵� socket
    SOCKET getSocket() const;

    // �������������Ϣ
    int sendMessage(const char* str, const int len);

    // ���÷�������ǰ��������
    void setCurrentConnections(const int currentConnections);

    // ��ȡ��������ǰ��������
    int getCurrentConnections() const;

    // ����������
    void addOnlinePlayer(const OnlinePlayerInfo onlinePlayerInfo);

    // ��ʼ�����
    void initializePlayers();

private:
    char ipv4[IPV4_ADDRESS_MAX_LENGTH + 1];   // IPv4 ��ַ
    int port;                                 // �˿�
    WSADATA wsaData;                          // Windows Sockets API
    SOCKET s;                                 // �ͻ��˵� socket
    struct sockaddr_in server;                // ��������ַ��Ϣ
    char message[BUFFER_SIZE];                // ���ݻ�����
    int recvSize;                             // �������ݴ�С
    std::vector<OnlinePlayerInfo> playerList; // ���������Ϣ
    int currentConnections;                   // ��������ǰ��������
};

#endif // !_ONLINE_MODE_CONTROL_H_