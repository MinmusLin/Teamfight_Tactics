/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Main.cpp
 * File Function: 程序入口点
 * Author:        林继申
 * Update Date:   2023/12/5
 ****************************************************************/

#define WIN32_LEAN_AND_MEAN // 排除 Windows 头文件中不常用的部分

#include <windows.h>
#include <tchar.h>
#include "platform/CCStdC.h"
#include "AppDelegate.h"
#include "cocos2d.h"

/*
 * Function Name:    _tWinMain
 * Function:         程序入口点
 * Input Parameters: HINSTANCE hInstance: 当前实例的句柄
 *                   HINSTANCE hPrevInstance: 前一个实例的句柄
 *                   LPTSTR lpCmdLine: 命令行参数的字符串
 *                   int nCmdShow: 控制窗口的显示状态
 * Return Value:     程序退出状态
 */
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    AppDelegate app;
    return cocos2d::Application::getInstance()->run();
}