/****************************************************************
 MIT License

 Copyright (c) 2023 Jishen Lin, Shuyi Liu, Zhaozhen Yang, Yukun Yang

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
 * Project Name:  Teamfight_Tactic
 * File Name:     GameMain.cpp
 * File Function: ��Ϸ������ڵ�
 * Author:        �ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#define WIN32_LEAN_AND_MEAN // �ų� Windows ͷ�ļ��в����õĲ���

#include <Windows.h>
#include <tchar.h>
#include "platform/CCStdC.h"
#include "AppDelegate/AppDelegate.h"

/*
 * Function Name:    _tWinMain
 * Function:         ��Ϸ������ڵ�
 * Input Parameters: HINSTANCE hInstance: ��ǰʵ���ľ��
 *                   HINSTANCE hPrevInstance: ǰһ��ʵ���ľ��
 *                   LPTSTR lpCmdLine: �����в������ַ���
 *                   int nCmdShow: ���ƴ��ڵ���ʾ״̬
 * Return Value:     �����˳�״̬
 */
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    // ��ʼ�������������
    srand(static_cast<unsigned int>(time(0)));

    // ��ʼ�� Cocos2d-x Ӧ�ó���ʵ��
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    AppDelegate app;
    return cocos2d::Application::getInstance()->run();
}