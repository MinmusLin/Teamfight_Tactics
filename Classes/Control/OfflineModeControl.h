/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeControl.h
 * File Function: OfflineModeControl类的定义
 * Author:        林继申
 * Update Date:   2023/12/20
 ****************************************************************/

#pragma once
#ifndef _OFFLINE_MODE_CONTROL_H_
#define _OFFLINE_MODE_CONTROL_H_

#include "Control.h"
#include "../Player/HumanPlayer.h"
#include "../Player/AIPlayer.h"
#include "Battle/Battle.h"

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

    // 获取 AI 玩家指针
    AIPlayer* getAIPlayer() const;

    // 获取对战类指针
    Battle* getBattle() const;

    // 初始化对战类
    void initializeBattle();

    // 释放对战类
    void releaseBattle();

private:
    HumanPlayer* humanPlayer; // 人类玩家
    AIPlayer* enemyPlayer;    // AI 玩家
    Battle* battle;           // 对战类
};

#endif // !_OFFLINE_MODE_CONTROL_H_