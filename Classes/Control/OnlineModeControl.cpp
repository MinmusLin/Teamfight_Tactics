/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeControl.cpp
 * File Function: OnlineModeControl���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/23
 ****************************************************************/

#include <iostream>
#include "OnlineModeControl.h"

// ���캯��
OnlineModeControl::OnlineModeControl(const int playersNum) :
    Control(playersNum)
{
    try {
        players = new HumanPlayer * [playersNum];
        for (int i = 0; i < playersNum; i++) {
            players[i] = new HumanPlayer("�������");
        }
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        for (int i = 0; i < playersNum; i++) {
            if (players[i]) {
                delete players[i];
            }
        }
        delete[] players;
        throw;
    }
}

// ��������
OnlineModeControl::~OnlineModeControl()
{
    for (int i = 0; i < maxPlayers; i++) {
        delete players[i];
    }
    delete[] players;
}