/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Control.cpp
 * File Function: Control���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/30
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

// �ͷŶ�ս��
void Control::releaseBattle()
{
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (battle->getChampion(i, j) != nullptr) {
                Champion* temp = battle->getChampion(i, j);
                battle->setEmpty(i, j);
                delete temp;
            }
            else {
                continue;
            }
        }
    }
    delete battle;
    battle = nullptr;
}