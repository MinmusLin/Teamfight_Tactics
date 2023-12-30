/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeControl.h
 * File Function: OfflineModeControl类的定义
 * Author:        杨宇琨、林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _OFFLINE_MODE_CONTROL_H_
#define _OFFLINE_MODE_CONTROL_H_

#include "Control.h"
#include "Player/AIPlayer.h"

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

    // 获取 AI 玩家指针
    AIPlayer* getAIPlayer() const;

    // 初始化对战类
    void initializeBattle();

private:
    AIPlayer* enemyPlayer; // AI 玩家
};

#endif // !_OFFLINE_MODE_CONTROL_H_