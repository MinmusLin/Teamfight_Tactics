/****************************************************************
 * Project Name:  Server
 * File Name:     Server.h
 * File Function: Server��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/19
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

private:
    WSADATA wsaData;                   // Windows Sockets API
    SOCKET serverSocket, clientSocket; // �������Ϳͻ��˵� socket
    struct sockaddr_in server, client; // �������Ϳͻ��˵ĵ�ַ��Ϣ
    char hostname[HOSTNAME_LENGHT];    // ������
    struct hostent* host;              // ������ַ
    int port;                          // �˿�
    int currentConnections;            // ��������ǰ��������
    std::vector<SOCKET> clients;       // �������ӵ��������Ŀͻ����׽���

    // �����ͳ��԰��׽���
    void createAndBindSocket();

    // �����ͽ��ܿͻ��˵��������󲢽��д���
    void handleConnections();
};

#endif // !_SERVER_H_