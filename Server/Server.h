/****************************************************************
 * Project Name:  Server
 * File Name:     Server.h
 * File Function: Server��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/27
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

    // ��Ԫ��������
    friend void clientHandler(SOCKET clientSocket, Server& server);

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

    // �����ͳ��԰��׽���
    void createAndBindSocket();

    // �����ͽ��ܿͻ��˵��������󲢽��д���
    void handleConnections();

    // �����������Ƿ������Ϸ
    bool areAllReady();

    // �������ӵ��������Ŀͻ����׽��ֺ�����ǳ�
    void outputClientsAndPlayerNames();
};

#endif // !_SERVER_H_