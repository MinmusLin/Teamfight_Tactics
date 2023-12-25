/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeControl.cpp
 * File Function: OfflineModeControl���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/21
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
    if (battle) {
        delete battle;
    }
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
    ChampionCategory(*myFlagMap)[BATTLE_MAP_COLUMNS];
    ChampionCategory(*enemyFlagMap)[BATTLE_MAP_COLUMNS];

    humanPlayer->getBattleMap(myFlagMap);
    enemyPlayer->getBattleMap(enemyFlagMap);
    //yykDebug
    (*enemyFlagMap)[0] = Champion1;
    (*(enemyFlagMap + 1))[2] = Champion2;
    (*(enemyFlagMap + 2))[5] = Champion3;
    (*(enemyFlagMap + 3))[6] = Champion3;
    (*(enemyFlagMap + 2))[8] = Champion4;

    try {
        battle = new Battle(myFlagMap, enemyFlagMap);
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        throw;
    }
}

// �ͷŶ�ս��
void OfflineModeControl::releaseBattle()
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