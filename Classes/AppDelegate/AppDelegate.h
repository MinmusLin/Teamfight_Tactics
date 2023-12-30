/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AppDelegate.h
 * File Function: AppDelegate��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _APP_DELEGATE_H_
#define _APP_DELEGATE_H_

#include "cocos2d.h"

/*
 * Class Name:     AppDelegate
 * Class Function: Cocos2d-x Ӧ�ó�����
 */
class AppDelegate : private cocos2d::Application {
public:
    // ��������
    virtual ~AppDelegate();

    // ��ʼ�� OpenGL ����������
    virtual void initGLContextAttrs();

    // ��Ӧ�ó������������׼��������ѭ��ʱ���ô˺���
    virtual bool applicationDidFinishLaunching();

    // ��Ӧ�ó�������̨ʱ���ô˺���
    virtual void applicationDidEnterBackground();

    // ��Ӧ�ó���Ӻ�̨���ص�ǰ̨ʱ���ô˺���
    virtual void applicationWillEnterForeground();
};

#endif // !_APP_DELEGATE_H_