/****************************************************************
 MIT License

 Copyright (c) 2024 Jishen Lin, Shuyi Liu, Zhaozhen Yang, Yukun Yang

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 ****************************************************************/

/****************************************************************
 * Project Name:  Server
 * File Name:     ServerMain.cpp
 * File Function: 服务器程序入口点
 * Author:        林继申
 * Update Date:   2023/12/27
 * License:       MIT License
 ****************************************************************/

#include <iostream>
#include <stdlib.h>
#include "Server.h"

/*
 * Function Name:    main
 * Function:         服务器程序入口点
 * Input Parameters: int argc: 参数个数
 *                   char* argv[]: 参数向量
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