/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HumanPlayer.h
 * File Function: HumanPlayer��Ķ���
 * Author:        �����ǡ��ּ���
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _HUMAN_PLAYER_H_
#define _HUMAN_PLAYER_H_

#include "Player.h"

/*
 * Class Name:     HumanPlayer
 * Class Function: ���������
 */
class HumanPlayer : public Player {
public:
    // ���캯��
    HumanPlayer(std::string nickname);
};

#endif // !_HUMAN_PLAYER_H_