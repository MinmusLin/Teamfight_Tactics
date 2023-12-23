/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.cpp
 * File Function: AIPlayer类的实现
 * Author:        林继申
 * Update Date:   2023/12/23
 ****************************************************************/

#include "AIPlayer.h"

// 构造函数
AIPlayer::AIPlayer(const std::string nickname, const Difficulty difficulty_) :
    Player(nickname),
    difficulty(difficulty_) {}

// AI 落棋算法
void AIPlayer::makeMoves()
{
    // TODO: 杨兆镇：AI落棋算法，难度根据私有变量difficulty决定
    // AI 落棋算法的难度会在设置界面全局调整
}