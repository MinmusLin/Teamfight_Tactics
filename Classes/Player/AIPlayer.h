/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.h
 * File Function: AIPlayer类的定义
 * Author:        杨兆镇、林继申
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _AI_PLAYER_H_
#define _AI_PLAYER_H_

#include "Player.h"

/*
 * Class Name:     AIPlayer
 * Class Function: AI 玩家类
 */
class AIPlayer : public Player {
public:
    // 构造函数
    AIPlayer(std::string nickname, Difficulty difficulty_);

private:
    Difficulty difficulty; // 游戏难度
};

#endif // !_AI_PLAYER_H_