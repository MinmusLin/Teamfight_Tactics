/****************************************************************
 * Project Name:  Server
 * File Name:     ServerMain.cpp
 * File Function: ������������ڵ�
 * Author:        �ּ���
 * Update Date:   2023/12/11
 ****************************************************************/

#include <iostream>
#include <stdlib.h>
#include "Server.h"

 /*
  * Function Name:    main
  * Function:         ������������ڵ�
  * Input Parameters: int argc
  *                   char* argv[]
  * Return Value:     �����˳�״̬
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