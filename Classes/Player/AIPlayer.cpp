/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.cpp
 * File Function: AIPlayer类的实现
 * Author:        林继申
 * Update Date:   2023/12/19
 ****************************************************************/

#include "AIPlayer.h"

// 构造函数
AIPlayer::AIPlayer(std::string nickname, Difficulty difficulty_) :
    Player(nickname),
    difficulty(difficulty_) {}