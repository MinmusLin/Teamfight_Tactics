/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     GameMain.cpp
 * File Function: ��Ϸ������ڵ�
 * Author:        �ּ���
 * Update Date:   2023/12/19
 ****************************************************************/

#define WIN32_LEAN_AND_MEAN // �ų� Windows ͷ�ļ��в����õĲ���

#include <Windows.h>
#include <tchar.h>
#include "platform/CCStdC.h"
#include "AppDelegate.h"
#include "cocos2d.h"

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
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    AppDelegate app;
    return cocos2d::Application::getInstance()->run();
}