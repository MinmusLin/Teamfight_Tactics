/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.cpp
 * File Function: AIPlayer���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/23
 ****************************************************************/

#include "AIPlayer.h"

// ���캯��
AIPlayer::AIPlayer(const std::string nickname, const Difficulty difficulty_) :
    Player(nickname),
    difficulty(difficulty_) {}

// AI �����㷨
void AIPlayer::makeMoves()
{
    // TODO: ������AI�����㷨���Ѷȸ���˽�б���difficulty����
    // AI �����㷨���ѶȻ������ý���ȫ�ֵ���
}