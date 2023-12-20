/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Battle.cpp
 * File Function: Battle类的实现
 * Author:        林继申
 * Update Date:   2023/12/20
 ****************************************************************/

#include <iostream>
#include "Battle.h"

// 构造函数
Battle::Battle(ChampionCategory myFlagMap[][BATTLE_MAP_COLUMNS], ChampionCategory enemyFlagMap[][BATTLE_MAP_COLUMNS])
{
    // TODO: 数组传递，注意镜像
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