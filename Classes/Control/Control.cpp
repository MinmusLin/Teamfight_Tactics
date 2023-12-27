/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Control.cpp
 * File Function: Control���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/27
 * License:       MIT License
 ****************************************************************/

#include "Control.h"

// ���캯��
Control::Control(const int maxPlayersNum) :
    maxPlayers(maxPlayersNum),
    humanPlayer(nullptr),
    battle(nullptr) {}

// ��ȡ�������ָ��
HumanPlayer* Control::getHumanPlayer() const
{
    return humanPlayer;
}

// ��ȡ��ս��ָ��
Battle* Control::getBattle() const
{
    return battle;
}