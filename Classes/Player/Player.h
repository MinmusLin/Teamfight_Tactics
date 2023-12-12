/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Player.h
 * File Function: Player��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include "proj.win32/Constant.h"

/*
 * Class Name:     Player
 * Class Function: �����
 */
class Player {
public:
    Player(std::string nickname);
protected:
    std::string name;                                                                  // ����ǳ�
    HeroCategory chessboardMap[HALF_CHESSBOARD_ROWS][CHESSBOARD_COLUMNS] = { NoHero }; // �����ͼ
};

#endif // !_PLAYER_H_