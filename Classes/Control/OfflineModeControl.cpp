/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeControl.cpp
 * File Function: OfflineModeControl���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/19
 ****************************************************************/

#include <iostream>
#include "OfflineModeControl.h"

USING_NS_CC;

// ���캯��
OfflineModeControl::OfflineModeControl() :
    Control(2)
{
    try {
        humanPlayer = new HumanPlayer(cocos2d::UserDefault::getInstance()->getStringForKey("PlayerName"));
        enemyPlayer = new AIPlayer("AI���", Easy);
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        if (humanPlayer) {
            delete humanPlayer;
        }
        if (enemyPlayer) {
            delete enemyPlayer;
        }
        throw;
    }
}

// ��������
OfflineModeControl::~OfflineModeControl()
{
    delete humanPlayer;
    delete enemyPlayer;
}

// ������ϰģʽ��Ϸ������
void OfflineModeControl::run(cocos2d::Scene* currentScene)
{
    humanPlayer->refreshShop(currentScene);
}