/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Battle.h
 * File Function: Battle类的定义
 * Author:        林继申
 * Update Date:   2023/12/23
 ****************************************************************/

#pragma once
#ifndef _BATTLE_H_
#define _BATTLE_H_

#include "Champion/Champion.h"
#include "proj.win32/Constant.h"
#include "Champion/Champion.h"

class Champion;

/*
 * Class Name:     Battle
 * Class Function: 对战类
 */
class Battle {
    friend class Champion;
public:
    // 构造函数
    Battle(const ChampionCategory myFlagMap[][BATTLE_MAP_COLUMNS], const ChampionCategory enemyFlagMap[][BATTLE_MAP_COLUMNS]);
<<<<<<< Updated upstream
=======

    // 获取场上英雄信息
    Champion* getChampion(const int& x, const int& y);

    // 获取场上我方剩余数量
    int getMyCount();

    // 获取场上敌方剩余数量
    int getEnemyCount();

    // 增加敌方数量
    void addEnemyCount();

    // 增加我方数量
    void addMyCount();

    // 重置数量
    void resetCount();

    // 将一个位置置空
    void setEmpty(const int& x, const int& y);

    // 放置一个棋子
    void placeChampion(const int& x, const int& y,Champion* champion);

    // 胜利
    void setWin();

    // 失败
    void setLose();

    // 平局
    void setDraw();
>>>>>>> Stashed changes

    // 析构函数
    ~Battle();

private:
    ChampionCategory championCategoryMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS]; // 战斗英雄地图
    Champion* championMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS];                // 战斗英雄指针
    int myCount ;                                                              // 我方英雄数量
    int enemyCount ;                                                           // 敌方英雄数量
    int isWinning;                                                            // 是否胜利
};

#endif // !_BATTLE_H_