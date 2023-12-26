/****************************************************************
 * Project Name:  Server
 * File Name:     Server.cpp
 * File Function: Server类的实现
 * Author:        林继申
 * Update Date:   2023/12/26
 ****************************************************************/

#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <ctime>
#include "Server.h"

/*
 * Function Name:    clientHandler
 * Function:         处理客户端连接
 * Input Parameters: SOCKET clientSocket: 客户端的套接字连接
 *                   std::vector<SOCKET>& clients: 存储所有客户端套接字的向量
 *                   int& currentConnections: 服务器当前连接数量
 * Return Value:     void
 */
static void clientHandler(SOCKET clientSocket, std::vector<SOCKET>& clients, int& currentConnections)
{
    char buffer[BUFFER_SIZE]; // 定义缓冲区用于存储接收的数据
    int recvSize; // 用于存储接收到的数据长度

    // 接受数据
    memset(buffer, 0, sizeof(buffer));
    while ((recvSize = recv(clientSocket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[recvSize] = '\0';

        // 获取当前服务器时间
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_c);
        std::cout << std::put_time(&now_tm, "[%H:%M:%S]");

        // 输出客户端 ID 和接收到的消息
        std::cout << " [Client ID: " << clientSocket << "] Message: " << buffer << std::endl;

        // 遍历所有客户端，将接收到的消息转发给其他客户端
        std::cout << "Broadcast: " << buffer << std::endl;
        for (const SOCKET& sock : clients) {
            send(sock, buffer, recvSize, 0);
        }
    }

    // 处理客户端断开连接
    if (recvSize == 0) {
        std::cout << "Client disconnected." << std::endl;
    }
    else {
        std::cerr << "Function recv failed with error: " << WSAGetLastError() << std::endl;
    }

    // 关闭与客户端的连接
    closesocket(clientSocket);
    std::cout << "Current connections: " << --currentConnections << std::endl;

    // 遍历所有客户端，将服务器当前连接数量转发给其他客户端
    sprintf(buffer, CURRENT_CONNECTIONS_FORMAT, currentConnections);
    std::cout << "Broadcast: " << buffer << std::endl;
    for (const SOCKET& sock : clients) {
        send(sock, buffer, CURRENT_CONNECTIONS_FORMAT_LENGTH, 0);
    }
}

// 构造函数
Server::Server()
{
    // 初始化服务器当前连接数量
    currentConnections = 0;

    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Function WSAStartupError failed with error: " << WSAGetLastError() << std::endl;
        exit(SOCKET_ERROR);
    }

    // 获取主机名
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        std::cerr << "Function gethostname failed with error: " << WSAGetLastError() << std::endl;
        exit(SOCKET_ERROR);
    }

    // 获取主机地址
    if ((host = gethostbyname(hostname)) == NULL) {
        std::cerr << "Function gethostbyname failed with error: " << WSAGetLastError() << std::endl;
        exit(SOCKET_ERROR);
    }

    // 准备 sockaddr_in 结构
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
}

// 析构函数
Server::~Server()
{
    closesocket(serverSocket);
    WSACleanup();
}

// 运行服务器
void Server::run()
{
    createAndBindSocket();
    handleConnections();
}

// 创建和尝试绑定套接字
void Server::createAndBindSocket()
{
    // 寻找可用端口
    for (port = MIN_PORT_ADDRESS; port <= MAX_PORT_ADDRESS; port++) {
        // 创建套接字
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == INVALID_SOCKET) {
            std::cerr << "Function socket failed with error: " << WSAGetLastError() << std::endl;
            exit(SOCKET_ERROR);
        }
        server.sin_port = htons(port);

        // 尝试绑定套接字
        if (bind(serverSocket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
            closesocket(serverSocket);
        }
        else {
            std::cout << "Server successfully created." << std::endl;
            char* ipv4 = inet_ntoa(*(struct in_addr*)*host->h_addr_list); // 转换地址格式
            std::cout << "IPv4: " << ipv4 << std::endl;
            std::cout << "Port: " << port << std::endl;
            break;
        }
    }

    // 无可用端口
    if (port == MAX_PORT_ADDRESS + 1) {
        std::cerr << "Error: Failed to bind to any port." << std::endl;
        exit(SOCKET_ERROR);
    }
}

// 监听和接受客户端的连接请求并进行处理
void Server::handleConnections()
{
    // 监听客户端
    listen(serverSocket, SOMAXCONN);
    int c = sizeof(struct sockaddr_in);
    std::cout << "Waiting for incoming connections..." << std::endl;

    // 接受客户端的连接请求并进行处理
    while (true) {
        if ((clientSocket = accept(serverSocket, (struct sockaddr*)&client, &c)) != INVALID_SOCKET) {
            if (currentConnections < MAX_CONNECTIONS) {
                // 接受连接
                std::cout << CONNECTION_ACCEPTED_MSG << std::endl;
                send(clientSocket, CONNECTION_ACCEPTED_MSG, strlen(CONNECTION_ACCEPTED_MSG), 0);
                clients.push_back(clientSocket);
                std::thread clientThread(clientHandler, clientSocket, std::ref(clients), std::ref(currentConnections));
                clientThread.detach();
                std::cout << "Current connections: " << ++currentConnections << std::endl;

                // 遍历所有客户端，将服务器当前连接数量转发给其他客户端
                char buffer[BUFFER_SIZE];
                sprintf(buffer, CURRENT_CONNECTIONS_FORMAT, currentConnections);
                std::cout << "Broadcast: " << buffer << std::endl;
                for (const SOCKET& sock : clients) {
                    send(sock, buffer, CURRENT_CONNECTIONS_FORMAT_LENGTH, 0);
                }
            }
            else {
                // 拒绝连接
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