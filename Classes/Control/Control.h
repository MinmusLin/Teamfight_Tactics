/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Control.h
 * File Function: Control��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/23
 ****************************************************************/

#pragma once
#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "cocos2d.h"

/*
 * Class Name:     Control
 * Class Function: ��Ϸ������
 */
class Control {
public:
    // ���캯��
    Control(const int maxPlayersNum);

protected:
    int maxPlayers; // ����������
};

#endif // !_CONTROL_H_