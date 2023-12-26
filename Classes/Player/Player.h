/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Player.h
 * File Function: Player类的定义
 * Author:        林继申
 * Update Date:   2023/12/27
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
    Player(const std::string nickname);

    // 获取战斗区地图
    void getBattleMap(ChampionCategory(*&battleMap)[BATTLE_MAP_COLUMNS]);

    // 减少玩家生命值
    void decreaseHealthPoints(const int num);

    // 获取玩家生命值
    int getHealthPoints() const;

    // 获取玩家昵称
    std::string getPlayerName() const;

protected:
    std::string name;                                               // 玩家昵称
    ChampionCategory battleMap[PLACE_MAP_ROWS][BATTLE_MAP_COLUMNS]; // 战斗区地图
    ChampionCategory waitingMap[WAITING_MAP_COUNT];                 // 候战区地图
    int healthPoints;                                               // 玩家生命值
};

#endif // !_PLAYER_H_