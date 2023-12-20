/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeControl.h
 * File Function: OfflineModeControl��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/19
 ****************************************************************/

#pragma once
#ifndef _OFFLINE_MODE_CONTROL_H_
#define _OFFLINE_MODE_CONTROL_H_

#include "Control.h"
#include "../Player/HumanPlayer.h"
#include "../Player/AIPlayer.h"

/*
 * Class Name:     OfflineModeControl
 * Class Function: ��ϰģʽ��Ϸ������
 */
class OfflineModeControl : public Control {
public:
    // ���캯��
    OfflineModeControl();

    // ��������
    ~OfflineModeControl();

    // ��ȡ�������ָ��
    HumanPlayer* getHumanPlayer() const;

    // ������ϰģʽ��Ϸ������
    void run(cocos2d::Scene* currentScene);

private:
    HumanPlayer* humanPlayer; // �������
    AIPlayer* enemyPlayer;    // AI ���
};

#endif // !_OFFLINE_MODE_CONTROL_H_