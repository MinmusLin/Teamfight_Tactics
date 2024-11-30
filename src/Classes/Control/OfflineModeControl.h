/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeControl.h
 * File Function: OfflineModeControl��Ķ���
 * Author:        ���������ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _OFFLINE_MODE_CONTROL_H_
#define _OFFLINE_MODE_CONTROL_H_

#include "Control.h"
#include "Player/AIPlayer.h"

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

    // ��ȡ AI ���ָ��
    AIPlayer* getAIPlayer() const;

    // ��ʼ����ս��
    void initializeBattle();

private:
    AIPlayer* enemyPlayer; // AI ���
};

#endif // !_OFFLINE_MODE_CONTROL_H_