/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Control.h
 * File Function: Control类的定义
 * Author:        林继申
 * Update Date:   2023/12/23
 ****************************************************************/

#pragma once
#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "cocos2d.h"

/*
 * Class Name:     Control
 * Class Function: 游戏控制类
 */
class Control {
public:
    // 构造函数
    Control(const int maxPlayersNum);

protected:
    int maxPlayers; // 最大玩家数量
};

#endif // !_CONTROL_H_