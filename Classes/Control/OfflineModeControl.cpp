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
    Control(2)
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

// 运行练习模式游戏控制类
void OfflineModeControl::run(cocos2d::Scene* currentScene)
{
    // TODO: 练习模式游戏控制类运行逻辑
}