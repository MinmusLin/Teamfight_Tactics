/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeControl.h
 * File Function: OfflineModeControl类的定义
 * Author:        林继申
 * Update Date:   2023/12/19
 ****************************************************************/

#pragma once
#ifndef _OFFLINE_MODE_CONTROL_H_
#define _OFFLINE_MODE_CONTROL_H_

#include "Control.h"
#include "../Player/HumanPlayer.h"
#include "../Player/AIPlayer.h"

/*
 * Class Name:     OfflineModeControl
 * Class Function: 练习模式游戏控制类
 */
class OfflineModeControl : public Control {
public:
    // 构造函数
    OfflineModeControl();

    // 析构函数
    ~OfflineModeControl();

    // 获取人类玩家指针
    HumanPlayer* getHumanPlayer() const;

    // 运行练习模式游戏控制类
    void run(cocos2d::Scene* currentScene);

private:
    HumanPlayer* humanPlayer; // 人类玩家
    AIPlayer* enemyPlayer;    // AI 玩家
};

#endif // !_OFFLINE_MODE_CONTROL_H_