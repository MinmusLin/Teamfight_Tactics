/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeControl.cpp
 * File Function: OfflineModeControl���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/20
 ****************************************************************/

#include <iostream>
#include "OfflineModeControl.h"
#include "Scene/OfflineModeBattleScene.h"

USING_NS_CC;

// ���캯��
OfflineModeControl::OfflineModeControl() :
    Control(2),
    battle(nullptr)
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

// ��ȡ�������ָ��
HumanPlayer* OfflineModeControl::getHumanPlayer() const
{
    return humanPlayer;
}

// ��ȡ AI ���ָ��
AIPlayer* OfflineModeControl::getAIPlayer() const
{
    return enemyPlayer;
}

// ��ȡ��ս��ָ��
Battle* OfflineModeControl::getBattle() const
{
    return battle;
}

// ��ʼ����ս��
void OfflineModeControl::initializeBattle()
{
    try {
        battle = new Battle();
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        throw;
    }
}

// �ͷŶ�ս��
void OfflineModeControl::releaseBattle()
{

}