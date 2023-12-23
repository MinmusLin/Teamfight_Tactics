/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Battle.cpp
 * File Function: Battle类的实现
 * Author:        林继申
 * Update Date:   2023/12/23
 ****************************************************************/

#include <iostream>
#include "Battle.h"

// 构造函数
Battle::Battle(const ChampionCategory myFlagMap[][BATTLE_MAP_COLUMNS], const ChampionCategory enemyFlagMap[][BATTLE_MAP_COLUMNS])
{
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            championCategoryMap[i][j] = myFlagMap[i][j];
            championCategoryMap[PLACE_MAP_ROWS - 1 - i][BATTLE_MAP_COLUMNS - 1 - j] = enemyFlagMap[i][j];
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