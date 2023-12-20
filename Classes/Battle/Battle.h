/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Battle.h
 * File Function: Battle类的定义
 * Author:        林继申
 * Update Date:   2023/12/20
 ****************************************************************/

#pragma once
#ifndef _BATTLE_H_
#define _BATTLE_H_

#include "Champion/Champion.h"
#include "proj.win32/Constant.h"

/*
 * Class Name:     Battle
 * Class Function: 对战类
 */
class Battle {
public:
    // 构造函数
    Battle(ChampionCategory myFlagMap[][BATTLE_MAP_COLUMNS], ChampionCategory enemyFlagMap[][BATTLE_MAP_COLUMNS]);

    // 析构函数
    ~Battle();

private:
    ChampionCategory championCategoryMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS]; // 战斗英雄地图
    Champion* championMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS];                // 战斗英雄指针
};

#endif // !_BATTLE_H_