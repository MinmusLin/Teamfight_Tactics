/****************************************************************
 * Project Name:  Server
 * File Name:     Server.h
 * File Function: Server��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _SERVER_H_
#define _SERVER_H_

#include <WinSock2.h>
#include <vector>
#include "..\proj.win32\Constant.h"

/*
 * Class Name:     Server
 * Class Function: ��������
 */
class Server {
public:
    // ���캯��
    Server();

    // ��������
    ~Server();

    // ���з�����
    void run();

    // ��ȡ�������ӵ��������Ŀͻ�������ǳ�
    std::vector<std::map<SOCKET, std::string>> getPlayerNames() const;

    // ��Ԫ��������
    friend void clientHandler(const SOCKET clientSocket, Server& server);

private:
    WSADATA wsaData;                                        // Windows Sockets API
    SOCKET serverSocket, clientSocket;                      // �������Ϳͻ��˵� socket
    struct sockaddr_in server, client;                      // �������Ϳͻ��˵ĵ�ַ��Ϣ
    char hostname[HOSTNAME_MAX_LENGHT];                     // ������
    struct hostent* host;                                   // ������ַ
    int port;                                               // �˿�
    int currentConnections;                                 // ��������ǰ��������
    std::vector<SOCKET> clients;                            // �������ӵ��������Ŀͻ����׽���
    std::vector<std::map<SOCKET, std::string>> playerNames; // �������ӵ��������Ŀͻ�������ǳ�
    std::vector<std::map<SOCKET, std::string>> battleMaps;  // �������ӵ��������Ŀͻ������ս������ͼ

    // �����ͳ��԰��׽���
    void createAndBindSocket();

    // �����ͽ��ܿͻ��˵��������󲢽��д���
    void handleConnections();

    // ����������ӵ��������Ŀͻ�����Ϣ���ѷ���
    bool areAllReady(const std::vector<std::map<SOCKET, std::string>>& data);

    // �رտͻ����׽���
    void closeClientSocket(const SOCKET clientSocket);

    // ���л��������ӵ��������Ŀͻ�������ǳ�
    std::string serializePlayerNames();
};

#endif // !_SERVER_H_