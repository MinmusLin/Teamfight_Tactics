/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Control.cpp
 * File Function: Control类的实现
 * Author:        林继申
 * Update Date:   2023/12/27
 * License:       MIT License
 ****************************************************************/

#include "Control.h"

// 构造函数
Control::Control(const int maxPlayersNum) :
    maxPlayers(maxPlayersNum),
    humanPlayer(nullptr),
    battle(nullptr) {}

// 获取人类玩家指针
HumanPlayer* Control::getHumanPlayer() const
{
    return humanPlayer;
}

// 获取对战类指针
Battle* Control::getBattle() const
{
    return battle;
}