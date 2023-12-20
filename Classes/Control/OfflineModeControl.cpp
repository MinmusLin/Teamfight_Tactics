/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeControl.cpp
 * File Function: OfflineModeControl类的实现
 * Author:        林继申
 * Update Date:   2023/12/20
 ****************************************************************/

#include <iostream>
#include "OfflineModeControl.h"
#include "Scene/OfflineModeBattleScene.h"

USING_NS_CC;

// 构造函数
OfflineModeControl::OfflineModeControl() :
    Control(2),
    battle(nullptr)
{
    try {
        humanPlayer = new HumanPlayer(cocos2d::UserDefault::getInstance()->getStringForKey("PlayerName"));
        enemyPlayer = new AIPlayer("AI玩家", Easy);
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

// 析构函数
OfflineModeControl::~OfflineModeControl()
{
    delete humanPlayer;
    delete enemyPlayer;
}

// 获取人类玩家指针
HumanPlayer* OfflineModeControl::getHumanPlayer() const
{
    return humanPlayer;
}

// 获取 AI 玩家指针
AIPlayer* OfflineModeControl::getAIPlayer() const
{
    return enemyPlayer;
}

// 获取对战类指针
Battle* OfflineModeControl::getBattle() const
{
    return battle;
}

// 初始化对战类
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

// 释放对战类
void OfflineModeControl::releaseBattle()
{

}