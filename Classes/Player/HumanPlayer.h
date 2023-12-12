/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HumanPlayer.h
 * File Function: HumanPlayer类的定义
 * Author:        刘淑仪、林继申
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _HUMAN_PLAYER_H_
#define _HUMAN_PLAYER_H_

#include "Player.h"

/*
 * Class Name:     HumanPlayer
 * Class Function: 人类玩家类
 */
class HumanPlayer : public Player {
public:
    // 构造函数
    HumanPlayer(std::string nickname);
};

#endif // !_HUMAN_PLAYER_H_