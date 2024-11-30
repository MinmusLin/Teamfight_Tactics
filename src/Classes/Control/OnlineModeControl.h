/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeControl.h
 * File Function: OnlineModeControl��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _ONLINE_MODE_CONTROL_H_
#define _ONLINE_MODE_CONTROL_H_

#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include "Control.h"

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

    // �ͻ����ڷ������� socket
    SOCKET getMySocket() const;

    // �������������Ϣ
    int sendMessage(const char* str, const int len);

    // ���÷�������ǰ��������
    void setCurrentConnections(const int currentConnections);

    // ��ȡ��������ǰ��������
    int getCurrentConnections() const;

    // ��ȡ�������ָ��
    HumanPlayer* getEnemyPlayer() const;

    // ���õ������ս������ͼ
    void setEnemyBattleMap(const ChampionCategory battleMap[][BATTLE_MAP_COLUMNS]);

    // ��ʼ����ս��
    void initializeBattle();

    // �����л��������ӵ��������Ŀͻ�������ǳ�
    void deserializePlayerNames(const std::string& data);

    // ��ȡ�������ӵ��������Ŀͻ�������ǳ�
    std::vector<std::map<SOCKET, std::string>> getPlayerNames() const;

    // ��ȡ�������ӵ��������Ŀͻ�����ҷ���
    std::vector<std::map<SOCKET, int>> getPlayerHealthPoints() const;

    // ���л����ս������ͼ
    std::string serializePlayerMap();

    // �����л����ս������ͼ
    void deserializeBattleMap(const std::string battleMapData, ChampionCategory battleMap[][BATTLE_MAP_COLUMNS]);

    // ��ȡ�ͻ��� socket �ڷ�����������
    int getSocketIndex();

private:
    char ipv4[IPV4_ADDRESS_MAX_LENGTH + 1];                 // IPv4 ��ַ
    int port;                                               // �˿�
    WSADATA wsaData;                                        // Windows Sockets API
    SOCKET s;                                               // �ͻ��˵� socket
    SOCKET mySocket;                                        // �ͻ����ڷ������� socket
    struct sockaddr_in server;                              // ��������ַ��Ϣ
    char message[BUFFER_SIZE];                              // ���ݻ�����
    int recvSize;                                           // �������ݴ�С
    int currentConnections;                                 // ��������ǰ��������
    HumanPlayer* enemyPlayer;                               // �������
    std::vector<std::map<SOCKET, std::string>> playerNames; // �������ӵ��������Ŀͻ�������ǳ�
    std::vector<std::map<SOCKET, int>> playerHealthPoints;  // �������ӵ��������Ŀͻ����������ֵ
    std::thread listeningThread;                            // ������������Ϣ�߳�
    std::atomic<bool> keepListening;                        // ������������Ϣ�߳̿��Ʊ�־
    mutable std::mutex healthPointsMutex;                   // ���ڱ��� playerHealthPoints �Ļ�������ȷ���̰߳�ȫ�ԣ�

    // ������������Ϣ�߳�
    void listenForServerMessages();

    // �����������ֵ
    void updatePlayerHealthPoints(const int healthPoint, const SOCKET socket);
};

#endif // !_ONLINE_MODE_CONTROL_H_