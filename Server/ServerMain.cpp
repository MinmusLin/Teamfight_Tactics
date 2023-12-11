/****************************************************************
 * Project Name:  Server
 * File Name:     ServerMain.cpp
 * File Function: 服务器程序入口点
 * Author:        林继申
 * Update Date:   2023/12/11
 ****************************************************************/

#include <iostream>
#include <stdlib.h>
#include "Server.h"

 /*
  * Function Name:    main
  * Function:         服务器程序入口点
  * Input Parameters: int argc
  *                   char* argv[]
  * Return Value:     程序退出状态
  */
int main(int argc, char* argv[])
{
    try {
        Server server;
        server.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}