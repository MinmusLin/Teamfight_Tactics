/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AIPlayer.h
 * File Function: AIPlayer��Ķ���
 * Author:        �������ּ���
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _AI_PLAYER_H_
#define _AI_PLAYER_H_

#include "Player.h"

/*
 * Class Name:     AIPlayer
 * Class Function: AI �����
 */
class AIPlayer : public Player {
public:
    // ���캯��
    AIPlayer(std::string nickname, Difficulty difficulty_);

private:
    Difficulty difficulty; // ��Ϸ�Ѷ�
};

#endif // !_AI_PLAYER_H_