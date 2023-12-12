/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeControl.h
 * File Function: OnlineModeControl类的定义
 * Author:        林继申
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _ONLINE_MODE_CONTROL_H_
#define _ONLINE_MODE_CONTROL_H_

#include "Control.h"
#include "../Player/HumanPlayer.h"

/*
 * Class Name:     OnlineModeControl
 * Class Function: 联机模式游戏控制类
 */
class OnlineModeControl : public Control {
public:
    // 构造函数
    OnlineModeControl(int maxPlayersNum) : Control(maxPlayersNum) {}

private:
    HumanPlayer** players; // 玩家列表
};

#endif // !_ONLINE_MODE_CONTROL_H_