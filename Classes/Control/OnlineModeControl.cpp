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
    //     WSAStartup �������� Windows Sockets API
    //     MAKEWORD(2,2) ָ������ 2.2 �汾�� Winsock
    //     �����ʼ��ʧ�ܣ����������Ϣ������ ConnectioError
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Function WSAStartup failed with error: " << WSAGetLastError() << std::endl;
        return ConnectionError;
    }

    // �����׽���
    //     AF_INET ��ʾ IPv4 ��ַ��
    //     SOCK_STREAM ��ʾ�ṩ˳�򡢿ɿ����������ӵ��ֽ���
    //     ����׽��ִ���ʧ�ܣ����������Ϣ������ ConnectioError
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Function socket failed with error: " << WSAGetLastError() << std::endl;
        return ConnectionError;
    }

    // ׼�� sockaddr_in �ṹ
    //     inet_addr ת�� IPv4 ��ַ���ı�����������ʽ
    //     htons ת���˿ں�Ϊ TCP/IP �����ֽ�˳��
    server.sin_addr.s_addr = inet_addr(ipv4);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // ���ӵ�Զ�̷�����
    //     connect ����������ָ���׽��ֵ�����
    //     �������ʧ�ܣ����������Ϣ������ ConnectioError
    if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Function connect failed with error: " << WSAGetLastError() << std::endl;
        return ConnectionError;
    }

    // �������Է�����������
    //     recv �������׽��ֽ�������
    //     �������ʧ�ܣ����������Ϣ������ ConnectioError
    if ((recvSize = recv(s, message, 1024, 0)) == SOCKET_ERROR) {
        std::cerr << "Function recv failed with error: " << WSAGetLastError() << std::endl;
        return ConnectionError;
    }

    // �������������Ӧ��Ϣ
    //     ����������������ӣ����� ConnectioAccepted
    //     ����������ܾ����ӣ������������������� ConnectioRefused
    if (!strcmp(message, CONNECTION_ACCEPTED_MSG)) {
        return ConnectionAccepted;
    }
    if (!strcmp(message, CONNECTION_REFUSED_MSG)) {
        return ConnectionRefused;
    }
    return ConnectionError;
}