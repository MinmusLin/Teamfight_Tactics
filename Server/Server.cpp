/****************************************************************
 * Project Name:  Server
 * File Name:     Server.cpp
 * File Function: Server���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <cstring>
#include "Server.h"

/*
 * Function Name:    clientHandler
 * Function:         ����ͻ�������
 * Input Parameters: const SOCKET clientSocket: �ͻ��˵��׽�������
 *                   Server& server: ��������
 * Return Value:     void
 */
void clientHandler(const SOCKET clientSocket, Server& server)
{
    char buffer[BUFFER_SIZE]; // ���建�������ڴ洢���յ�����
    int recvSize; // ���ڴ洢���յ������ݳ���

    // ��������
    memset(buffer, 0, sizeof(buffer));
    while ((recvSize = recv(clientSocket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[recvSize] = '\0';

        // ��ȡ��ǰ������ʱ��
        std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << std::put_time(std::localtime(&now), "[%H:%M:%S]");

        // ����ͻ��˺ͽ��յ�����Ϣ
        std::cout << " [Client: " << clientSocket << "] Message: " << buffer << std::endl;

        // �������������Ϣ
        if (!strncmp(buffer, BATTLE_MAP_IDENTIFIER, MESSAGE_IDENTIFIER_LENGTH)) {
            char battleMap[BUFFER_SIZE];
            sscanf(buffer, BATTLE_MAP_FORMAT, battleMap);
            for (auto& map : server.battleMaps) {
                if (map.find(clientSocket) != map.end()) {
                    map[clientSocket] = static_cast<std::string>(battleMap);
                    break;
                }
            }
        }

        // �������ս������ͼ��Ϣ
        if (!strncmp(buffer, PLAYER_NAME_IDENTIFIER, MESSAGE_IDENTIFIER_LENGTH)) {
            char playerName[BUFFER_SIZE];
            sscanf(buffer, PLAYER_NAME_FORMAT, playerName);
            for (auto& map : server.playerNames) {
                if (map.find(clientSocket) != map.end()) {
                    map[clientSocket] = static_cast<std::string>(playerName);
                    break;
                }
            }
        }

        // �����������ֵ��Ϣ
        if (!strncmp(buffer, HEALTH_POINTS_IDENTIFIER, MESSAGE_IDENTIFIER_LENGTH)) {
            for (const SOCKET& sock : server.clients) {
                send(sock, buffer, strlen(buffer), 0);
            }
        }

        // ����Ƿ�ʼ��Ϸ
        if (server.areAllReady(server.playerNames)) {
            strcpy(buffer, server.serializePlayerNames().c_str());
            std::cout << "Broadcast: " << buffer << std::endl;
            for (const SOCKET& sock : server.clients) {
                send(sock, buffer, strlen(buffer), 0);
            }
        }

        // ����Ƿ�ʼս��
        if (server.areAllReady(server.battleMaps)) {
            for (size_t i = 0; i < server.clients.size(); i++) {
                sprintf(buffer, BATTLE_MAP_FORMAT, server.getPairedData(server.battleMaps, i).c_str());
                std::cout << "Send Client " << server.clients[i ^ 1] << "[" << (i ^ 1) << "]'s BattleMap to Client " << server.clients[i] << "[" << i << "]: " << buffer << std::endl;
                send(server.clients[i], buffer, strlen(buffer), 0);
            }
            server.clearStrings(server.battleMaps);
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
    server.closeClientSocket(clientSocket);
    std::cout << "Current connections: " << --server.currentConnections << std::endl;

    // �������пͻ��ˣ�����������ǰ��������ת���������ͻ���
    sprintf(buffer, CURRENT_CONNECTIONS_FORMAT, server.currentConnections);
    std::cout << "Broadcast: " << buffer << std::endl;
    for (const SOCKET& sock : server.clients) {
        send(sock, buffer, strlen(buffer), 0);
    }

    // �����ӳ�ȷ����Ϣ�������ͻ���
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000 * SERVER_REFRESH_INTERVAL_MAGNIFICATION * SERVER_REFRESH_INTERVAL)));

    // ����Ƿ�ʼ��Ϸ
    if (server.areAllReady(server.playerNames)) {
        strcpy(buffer, server.serializePlayerNames().c_str());
        std::cout << "Broadcast: " << buffer << std::endl;
        for (const SOCKET& sock : server.clients) {
            send(sock, buffer, strlen(buffer), 0);
        }
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
                send(clientSocket, CONNECTION_ACCEPTED_MSG, static_cast<int>(strlen(CONNECTION_ACCEPTED_MSG)), 0);
                clients.push_back(clientSocket);
                playerNames.push_back({ {clientSocket, ""} });
                battleMaps.push_back({ {clientSocket, ""} });
                std::thread clientThread(clientHandler, clientSocket, std::ref(*this));
                clientThread.detach();
                std::cout << "Current connections: " << ++currentConnections << std::endl;

                // �������пͻ��ˣ�����������ǰ��������ת���������ͻ���
                char buffer[BUFFER_SIZE];
                sprintf(buffer, CURRENT_CONNECTIONS_FORMAT, currentConnections);
                std::cout << "Broadcast: " << buffer << std::endl;
                for (const SOCKET& sock : clients) {
                    send(sock, buffer, static_cast<int>(strlen(buffer)), 0);
                }
            }
            else {
                // �ܾ�����
                std::cout << "Maximum connections reached. " << CONNECTION_REFUSED_MSG << std::endl;
                send(clientSocket, CONNECTION_REFUSED_MSG, static_cast<int>(strlen(CONNECTION_REFUSED_MSG)), 0);
                closeClientSocket(clientSocket);
            }
        }
        else {
            std::cerr << "Function accept failed with error: " << WSAGetLastError() << std::endl;
            break;
        }
    }
}

// ����������ӵ��������Ŀͻ�����Ϣ���ѷ���
bool Server::areAllReady(const std::vector<std::map<SOCKET, std::string>>& data)
{
    for (const SOCKET& clientSocket : clients) {
        bool nameFound = false;
        for (const auto& map : data) {
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

// �رտͻ����׽���
void Server::closeClientSocket(const SOCKET clientSocket)
{
    // �ر���ͻ��˵�����
    closesocket(clientSocket);

    // �Ƴ��ͻ����׽���
    auto clientsIndex = std::find(clients.begin(), clients.end(), clientSocket);
    if (clientsIndex != clients.end()) {
        clients.erase(clientsIndex);
    }

    // �Ƴ��ͻ�������ǳ�
    auto clientSocketIndex = std::find_if(playerNames.begin(), playerNames.end(), [clientSocket](const std::map<SOCKET, std::string>& m) {
        return m.find(clientSocket) != m.end();
        });
    if (clientSocketIndex != playerNames.end()) {
        playerNames.erase(clientSocketIndex);
    }

    // �Ƴ��ͻ������ս������ͼ
    clientSocketIndex = std::find_if(battleMaps.begin(), battleMaps.end(), [clientSocket](const std::map<SOCKET, std::string>& m) {
        return m.find(clientSocket) != m.end();
        });
    if (clientSocketIndex != battleMaps.end()) {
        battleMaps.erase(clientSocketIndex);
    }
}

// ���л��������ӵ��������Ŀͻ�������ǳ�
std::string Server::serializePlayerNames()
{
    std::stringstream ss;
    ss << START_GAME_MSG;
    for (const auto& map : playerNames) {
        for (const auto& pair : map) {
            ss << pair.first << ":" << pair.second << ",";
        }
        ss.seekp(-1, ss.cur);
        ss << ";";
    }
    return ss.str();
}

// ��ȡ��ֵ������
std::string Server::getPairedData(const std::vector<std::map<SOCKET, std::string>>& data, size_t index)
{
    if (index % 2 == 0) { // ����ż����������������һ�������������ַ�������
        if (index + 1 < clients.size()) {
            SOCKET pairedSocket = clients[index + 1];
            for (const auto& map : data) {
                auto it = map.find(pairedSocket);
                if (it != map.end()) {
                    return it->second;
                }
            }
        }
    }
    else { // ��������������������ǰһ��ż���������ַ�������
        if (index >= 1) {
            SOCKET pairedSocket = clients[index - 1];
            for (const auto& map : data) {
                auto it = map.find(pairedSocket);
                if (it != map.end()) {
                    return it->second;
                }
            }
        }
    }
    return "";
}

// ����������ӵ��������Ŀͻ�������ַ�������
void Server::clearStrings(std::vector<std::map<SOCKET, std::string>>& data)
{
    for (auto& map : data) {
        for (auto& pair : map) {
            pair.second = "";
        }
    }
}