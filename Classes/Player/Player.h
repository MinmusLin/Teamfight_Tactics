/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Player.h
 * File Function: Player类的定义
 * Author:        林继申
 * Update Date:   2023/12/20
 ****************************************************************/

#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "proj.win32/Constant.h"

/*
 * Class Name:     Player
 * Class Function: 玩家类
 */
class Player {
public:
    // 构造函数
    Player(std::string nickname);

    // 获取战斗区地图
    ChampionCategory** getBattleMap() const;

protected:
    std::string name;                                                // 玩家昵称
    ChampionCategory battleMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS]; // 战斗区地图
    ChampionCategory waitingMap[WAITING_MAP_COUNT];                  // 候战区地图
};

#endif // !_PLAYER_H_