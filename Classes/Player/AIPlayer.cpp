/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.cpp
 * File Function: AIPlayer���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/19
 ****************************************************************/

#include "AIPlayer.h"

// ���캯��
AIPlayer::AIPlayer(std::string nickname, Difficulty difficulty_) :
    Player(nickname),
    difficulty(difficulty_) {}