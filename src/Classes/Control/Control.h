/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Control.h
 * File Function: Control类的定义
 * Author:        林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "cocos2d.h"
#include "Player/HumanPlayer.h"
#include "Battle/Battle.h"

/*
 * Class Name:     Control
 * Class Function: 游戏控制类
 */
class Control {
public:
    // 构造函数
    Control(const int maxPlayersNum);

    // 获取人类玩家指针
    HumanPlayer* getHumanPlayer() const;

    // 获取对战类指针
    Battle* getBattle() const;

    // 释放对战类
    void releaseBattle();

protected:
    int maxPlayers;           // 最大玩家数量
    HumanPlayer* humanPlayer; // 人类玩家
    Battle* battle;           // 对战类
};

#endif // !_CONTROL_H_