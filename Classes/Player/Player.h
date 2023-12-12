/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Player.h
 * File Function: Player类的定义
 * Author:        林继申
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include "proj.win32/Constant.h"

/*
 * Class Name:     Player
 * Class Function: 玩家类
 */
class Player {
public:
    Player(std::string nickname);
protected:
    std::string name;                                                                  // 玩家昵称
    HeroCategory chessboardMap[HALF_CHESSBOARD_ROWS][CHESSBOARD_COLUMNS] = { NoHero }; // 置棋地图
};

#endif // !_PLAYER_H_