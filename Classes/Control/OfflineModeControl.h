/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeControl.h
 * File Function: OfflineModeControl��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _OFFLINE_MODE_CONTROL_H_
#define _OFFLINE_MODE_CONTROL_H_

#include <iostream>
#include "cocos2d.h"
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
    OfflineModeControl() : Control(2)
    {
        try {
            humanPlayer = new HumanPlayer(cocos2d::UserDefault::getInstance()->getStringForKey("PlayerName"));
            enemyPlayer = new AIPlayer("AI���");
        }
        catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            throw;
        }
    }

private:
    HumanPlayer* humanPlayer; // �������
    AIPlayer* enemyPlayer;    // AI ���
};

#endif // !_OFFLINE_MODE_CONTROL_H_