/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeControl.h
 * File Function: OnlineModeControl��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _ONLINE_MODE_CONTROL_H_
#define _ONLINE_MODE_CONTROL_H_

#include "Control.h"
#include "../Player/HumanPlayer.h"

/*
 * Class Name:     OnlineModeControl
 * Class Function: ����ģʽ��Ϸ������
 */
class OnlineModeControl : public Control {
public:
    // ���캯��
    OnlineModeControl(int maxPlayersNum) : Control(maxPlayersNum) {}

private:
    HumanPlayer** players; // ����б�
};

#endif // !_ONLINE_MODE_CONTROL_H_