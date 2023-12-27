/****************************************************************
 * Project Name:  Server
 * File Name:     Server.cpp
 * File Function: Server���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/27
 * License:       MIT License
 ****************************************************************/

#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <cstring>
#include "Server.h"

/*
 * Function Name:    clientHandler
 * Function:         ����ͻ�������
 * Input Parameters: SOCKET clientSocket: �ͻ��˵��׽�������
 *                   Server& server: ��������
 * Return Value:     void
 */
void clientHandler(SOCKET clientSocket, Server& server)
{
    char buffer[BUFFER_SIZE]; // ���建�������ڴ洢���յ�����
    int recvSize; // ���ڴ洢���յ������ݳ���

    // ��������
    memset(buffer, 0, sizeof(buffer));
    while ((recvSize = recv(clientSocket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[recvSize] = '\0';

        // ��ȡ��ǰ������ʱ��
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_c);
        std::cout << std::put_time(&now_tm, "[%H:%M:%S]");

        // ����ͻ��� ID �ͽ��յ�����Ϣ
        std::cout << " [Client ID: " << clientSocket << "] Message: " << buffer << std::endl;

        // �������������Ϣ
        if (!strncmp(buffer, "PlayerName", MESSAGE_IDENTIFIER_LENGTH)) {
            char playerName[BUFFER_SIZE];
            sscanf(buffer, PLAYER_NAME_FORMAT, playerName);
            for (auto& map : server.playerNames) {
                if (map.find(clientSocket) != map.end()) {
                    map[clientSocket] = static_cast<std::string>(playerName);
                    std::cout << "Receive from " << clientSocket << " : " << map[clientSocket] << std::endl;
                    break;
                }
            }
            if (server.areAllReady()) {
                std::cout << "Broadcast: " << START_GAME_MSG << std::endl;
                for (const SOCKET& sock : server.clients) {
                    send(sock, START_GAME_MSG, strlen(START_GAME_MSG), 0);
                }
            }
        }

        // �������пͻ��ˣ������յ�����Ϣת���������ͻ���
        std::cout << "Broadcast: " << buffer << std::endl;
        for (const SOCKET& sock : server.clients) {
            send(sock, buffer, recvSize, 0);
        }
    }

    // ����ͻ��˶Ͽ�����
    if (recvSize == 0) {
        std::cout << "Client disconnected." << std::endl;
    }
    else {
        std::cerr << "Function recv failed with error: " << WSAGetLastError() << std::endl;
    }

    // �ر���ͻ��˵�����
    closesocket(clientSocket);
    server.clients.erase(std::remove(server.clients.begin(), server.clients.end(), clientSocket), server.clients.end());
    server.playerNames.erase(std::remove_if(server.playerNames.begin(), server.playerNames.end(), [clientSocket](const std::map<SOCKET, std::string>& m) {
        return m.find(clientSocket) != m.end();
        }), server.playerNames.end());
    std::cout << "Current connections: " << --server.currentConnections << std::endl;
    server.outputClientsAndPlayerNames();

    // �������пͻ��ˣ�����������ǰ��������ת���������ͻ���
    sprintf(buffer, CURRENT_CONNECTIONS_FORMAT, server.currentConnections);
    std::cout << "Broadcast: " << buffer << std::endl;
    for (const SOCKET& sock : server.clients) {
        send(sock, buffer, strlen(buffer), 0);
    }
}

// ���캯��
Server::Server() :
    currentConnections(0)
{
    // ��ʼ�� Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Function WSAStartupError failed with error: " << WSAGetLastError() << std::endl;
        exit(SOCKET_ERROR);
    }

    // ��ȡ������
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        std::cerr << "Function gethostname failed with error: " << WSAGetLastError() << std::endl;
        exit(SOCKET_ERROR);
    }

    // ��ȡ������ַ
    if ((host = gethostbyname(hostname)) == NULL) {
        std::cerr << "Function gethostbyname failed with error: " << WSAGetLastError() << std::endl;
        exit(SOCKET_ERROR);
    }

    // ׼�� sockaddr_in �ṹ
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
}

// ��������
Server::~Server()
{
    closesocket(serverSocket);
    WSACleanup();
}

// ���з�����
void Server::run()
{
    createAndBindSocket();
    handleConnections();
}

// �����ͳ��԰��׽���
void Server::createAndBindSocket()
{
    // Ѱ�ҿ��ö˿�
    for (port = MIN_PORT_ADDRESS; port <= MAX_PORT_ADDRESS; port++) {
        // �����׽���
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == INVALID_SOCKET) {
            std::cerr << "Function socket failed with error: " << WSAGetLastError() << std::endl;
            exit(SOCKET_ERROR);
        }
        server.sin_port = htons(port);

        // ���԰��׽���
        if (bind(serverSocket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
            closesocket(serverSocket);
        }
        else {
            std::cout << "Server successfully created." << std::endl;
            char* ipv4 = inet_ntoa(*(struct in_addr*)*host->h_addr_list); // ת����ַ��ʽ
            std::cout << "IPv4: " << ipv4 << std::endl;
            std::cout << "Port: " << port << std::endl;
            break;
        }
    }

    // �޿��ö˿�
    if (port == MAX_PORT_ADDRESS + 1) {
        std::cerr << "Error: Failed to bind to any port." << std::endl;
        exit(SOCKET_ERROR);
    }
}

// �����ͽ��ܿͻ��˵��������󲢽��д���
void Server::handleConnections()
{
    // �����ͻ���
    listen(serverSocket, SOMAXCONN);
    int c = sizeof(struct sockaddr_in);
    std::cout << "Waiting for incoming connections..." << std::endl;

    // ���ܿͻ��˵��������󲢽��д���
    while (true) {
        if ((clientSocket = accept(serverSocket, (struct sockaddr*)&client, &c)) != INVALID_SOCKET) {
            if (currentConnections < MAX_CONNECTIONS) {
                // ��������
                std::cout << CONNECTION_ACCEPTED_MSG << std::endl;
                send(clientSocket, CONNECTION_ACCEPTED_MSG, strlen(CONNECTION_ACCEPTED_MSG), 0);
                clients.push_back(clientSocket);
                playerNames.push_back({ {clientSocket, ""} });
                std::thread clientThread(clientHandler, clientSocket, std::ref(*this));
                clientThread.detach();
                std::cout << "Current connections: " << ++currentConnections << std::endl;
                outputClientsAndPlayerNames();

                // �������пͻ��ˣ�����������ǰ��������ת���������ͻ���
                char buffer[BUFFER_SIZE];
                sprintf(buffer, CURRENT_CONNECTIONS_FORMAT, currentConnections);
                std::cout << "Broadcast: " << buffer << std::endl;
                for (const SOCKET& sock : clients) {
                    send(sock, buffer, strlen(buffer), 0);
                }
            }
            else {
                // �ܾ�����
                std::cout << "Maximum connections reached. " << CONNECTION_REFUSED_MSG << std::endl;
                send(clientSocket, CONNECTION_REFUSED_MSG, strlen(CONNECTION_REFUSED_MSG), 0);
                closesocket(clientSocket);
            }
        }
        else {
            std::cerr << "Function accept failed with error: " << WSAGetLastError() << std::endl;
            break;
        }
    }
}

// �����������Ƿ������Ϸ
bool Server::areAllReady()
{
    for (const SOCKET& clientSocket : clients) {
        bool nameFound = false;
        for (const auto& map : playerNames) {
            auto it = map.find(clientSocket);
            if (it != map.end()) {
                nameFound = true;
                if (it->second == "") {
                    return false;
                }
                break;
            }
        }
        if (!nameFound) {
            return false;
        }
    }
    return true;
}

// �������ӵ��������Ŀͻ����׽��ֺ�����ǳ�
void Server::outputClientsAndPlayerNames()
{
    std::cout << "Current Clients: ";
    for (const SOCKET& clientSocket : clients) {
        std::cout << clientSocket << " ";
    }
    std::cout << std::endl;
    std::cout << "Current Player Names: " << std::endl;
    for (const auto& playerMap : playerNames) {
        for (const auto& pair : playerMap) {
            std::cout << "Socket: " << pair.first << " - Player Name: " << pair.second << std::endl;
        }
    }
}