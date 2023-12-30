/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Control.h
 * File Function: Control��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "cocos2d.h"
#include "Player/HumanPlayer.h"
#include "Battle/Battle.h"

/*
 * Class Name:     Control
 * Class Function: ��Ϸ������
 */
class Control {
public:
    // ���캯��
    Control(const int maxPlayersNum);

    // ��ȡ�������ָ��
    HumanPlayer* getHumanPlayer() const;

    // ��ȡ��ս��ָ��
    Battle* getBattle() const;

    // �ͷŶ�ս��
    void releaseBattle();

protected:
    int maxPlayers;           // ����������
    HumanPlayer* humanPlayer; // �������
    Battle* battle;           // ��ս��
};

#endif // !_CONTROL_H_