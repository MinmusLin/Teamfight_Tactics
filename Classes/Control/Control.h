/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Control.h
 * File Function: Control��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _CONTROL_H_
#define _CONTROL_H_

/*
 * Class Name:     Control
 * Class Function: ��Ϸ������
 */
class Control {
public:
    // ���캯��
    Control(int maxPlayersNum);

protected:
    int maxPlayers; // ����������
};

#endif // !_CONTROL_H_