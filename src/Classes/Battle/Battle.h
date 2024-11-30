/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Battle.h
 * File Function: Battle类的定义
 * Author:        杨宇琨、林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _BATTLE_H_
#define _BATTLE_H_

#include <vector>
#include "Champion/Champion.h"
#include "proj.win32/Constant.h"

// Champion 类前声明（用于解决循环依赖）
class Champion;

/*
 * Class Name:     Battle
 * Class Function: 对战类
 */
class Battle {
public:
    // 构造函数
    Battle(const ChampionCategory myFlagMap[][BATTLE_MAP_COLUMNS], const ChampionCategory enemyFlagMap[][BATTLE_MAP_COLUMNS]);

    // 析构函数
    ~Battle();

    // 获取战斗英雄指针
    Champion* getChampion(const int& x, const int& y);

    // 获取我方战斗英雄数量
    int getMyCount();

    // 获取敌方战斗英雄数量
    int getEnemyCount();

    // 增加我方战斗英雄数量
    void addMyCount();

    // 增加敌方战斗英雄数量
    void addEnemyCount();

    // 重置战斗英雄数量
    void resetCount();

    // 移除战斗英雄
    void setEmpty(const int& x, const int& y);

    // 放置战斗英雄
    void placeChampion(const int& x, const int& y, Champion* champion);

    // 设置战斗胜负状态
    void setBattleSituation(const BattleSituation battleSituation);

    // 获取我方羁绊效果
    std::vector<int> getMyBond() const;

    // 获取敌方羁绊效果
    std::vector<int> getEnemyBond() const;

    // 羁绊效果
    void bondEffect(const Bond bond, const bool isMyFlag);

    // 声明友元类
    friend class Champion;

private:
    ChampionCategory championCategoryMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS]; // 战斗区地图
    Champion* championMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS];                // 战斗区战斗英雄指针
    int myCount;                                                               // 我方战斗英雄数量
    int enemyCount;                                                            // 敌方战斗英雄数量
    BattleSituation battleSituation;                                           // 战斗胜负状态
    std::vector<int> myBond;                                                   // 我方羁绊效果
    std::vector<int> enemyBond;                                                // 敌方羁绊效果
};

#endif // !_BATTLE_H_