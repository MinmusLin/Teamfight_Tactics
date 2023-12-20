/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeControl.h
 * File Function: OfflineModeControl��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/20
 ****************************************************************/

#pragma once
#ifndef _OFFLINE_MODE_CONTROL_H_
#define _OFFLINE_MODE_CONTROL_H_

#include "Control.h"
#include "../Player/HumanPlayer.h"
#include "../Player/AIPlayer.h"
#include "Battle/Battle.h"

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

    // ��ȡ AI ���ָ��
    AIPlayer* getAIPlayer() const;

    // ��ȡ��ս��ָ��
    Battle* getBattle() const;

    // ��ʼ����ս��
    void initializeBattle();

    // �ͷŶ�ս��
    void releaseBattle();

private:
    HumanPlayer* humanPlayer; // �������
    AIPlayer* enemyPlayer;    // AI ���
    Battle* battle;           // ��ս��
};

#endif // !_OFFLINE_MODE_CONTROL_H_