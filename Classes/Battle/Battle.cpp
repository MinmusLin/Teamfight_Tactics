/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Battle.cpp
 * File Function: Battle类的实现
 * Author:        林继申
 * Update Date:   2023/12/23
 ****************************************************************/

#include <iostream>
#include "Battle.h"
#include "Champion/Champion.h"

<<<<<<< Updated upstream
// 构造函数
=======
 // 构造函数
>>>>>>> Stashed changes
Battle::Battle(const ChampionCategory myFlagMap[][BATTLE_MAP_COLUMNS], const ChampionCategory enemyFlagMap[][BATTLE_MAP_COLUMNS])
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
                try {
                    championMap[i][j] = new Champion(championCategoryMap[i][j]);
                }
                catch (const std::bad_alloc& e) {
                    std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                    throw;
                }
                championMap[i][j]->setCurrentPosition(i, j);
                // 设置阵营
                if (i < 4) {
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

// 获取场上英雄信息
Champion* Battle::getChampion(const int& x, const int& y)
{
    return championMap[x][y];
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

// 获取场上我方剩余数量
int Battle::getMyCount()
{
    return myCount;
}

// 获取场上敌方剩余数量
int Battle::getEnemyCount()
{
    return enemyCount;
}

// 增加敌方数量
void Battle::addEnemyCount()
{
    enemyCount++;
}

// 增加我方数量
void Battle::addMyCount()
{
    myCount++;
}

// 重置数量
void Battle::resetCount()
{
    enemyCount = 0;
    myCount = 0;
}

// 将一个位置置空
void Battle::setEmpty(const int& x, const int& y)
{
    championMap[x][y] = nullptr;
}

// 放置一个棋子
void Battle::placeChampion(const int& x, const int& y, Champion* champion)
{
    championMap[x][y] = champion;
}

// 胜利
void Battle::setWin()
{
    isWinning = win;
}

// 失败
void Battle::setLose()
{
    isWinning = lose;
}

// 平局
void Battle::setDraw()
{
    isWinning = draw;
}
