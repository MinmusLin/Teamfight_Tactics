/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeControl.cpp
 * File Function: OnlineModeControl���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/26
 ****************************************************************/

#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <cstring>
#include "OnlineModeControl.h"

// ���캯��
OnlineModeControl::OnlineModeControl(std::string ipv4, std::string portStr) :
    port(std::stoi(portStr)),
    Control(0)
{
    strcpy(this->ipv4, ipv4.c_str());
}

// ��������
OnlineModeControl::~OnlineModeControl()
{
    closesocket(s);
    WSACleanup();
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