/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Battle.cpp
 * File Function: Battle类的实现
 * Author:        杨宇琨、林继申
 * Update Date:   2023/12/27
 * License:       MIT License
 ****************************************************************/

#include <iostream>
#include "Battle.h"

// 构造函数
Battle::Battle(const ChampionCategory myFlagMap[][BATTLE_MAP_COLUMNS], const ChampionCategory enemyFlagMap[][BATTLE_MAP_COLUMNS]) :
    enemyCount(0),
    myCount(0),
    battleSituation(Draw)
{
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            championCategoryMap[i][j] = myFlagMap[i][j];
            championCategoryMap[BATTLE_MAP_ROWS - 1 - i][BATTLE_MAP_COLUMNS - 1 - j] = enemyFlagMap[i][j];
        }
    }
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (championCategoryMap[i][j] != NoChampion) {
                // 创建战斗英雄
                try {
                    championMap[i][j] = new Champion(championCategoryMap[i][j]);
                }
                catch (const std::bad_alloc& e) {
                    std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                    throw;
                }
                championMap[i][j]->setCurrentPosition(i, j);

                // 设置战斗英雄阵营
                if (i < PLACE_MAP_ROWS) {
                    myCount++;
                    championMap[i][j]->setCamp(true);
                }
                else {
                    enemyCount++;
                    championMap[i][j]->setCamp(false);
                }
            }
            else {
                championMap[i][j] = nullptr;
            }
        }
    }
}

// 析构函数
Battle::~Battle()
{
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (championMap[i][j] != nullptr) {
                delete championMap[i][j];
            }
        }
    }
}

// 获取战斗英雄指针
Champion* Battle::getChampion(const int& x, const int& y)
{
    return championMap[x][y];
}

// 获取我方战斗英雄数量
int Battle::getMyCount()
{
    return myCount;
}

// 获取敌方战斗英雄数量
int Battle::getEnemyCount()
{
    return enemyCount;
}

// 增加我方战斗英雄数量
void Battle::addMyCount()
{
    myCount++;
}

// 增加敌方战斗英雄数量
void Battle::addEnemyCount()
{
    enemyCount++;
}

// 重置战斗英雄数量
void Battle::resetCount()
{
    myCount = 0;
    enemyCount = 0;
}

// 移除战斗英雄
void Battle::setEmpty(const int& x, const int& y)
{
    championMap[x][y] = nullptr;
}

// 放置战斗英雄
void Battle::placeChampion(const int& x, const int& y, Champion* champion)
{
    championMap[x][y] = champion;
}

// 设置战斗胜负状态
void Battle::setBattleSituation(const BattleSituation battleSituation)
{
    this->battleSituation = battleSituation;
}