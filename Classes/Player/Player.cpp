/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Player.cpp
 * File Function: Player类的实现
 * Author:        林继申
 * Update Date:   2023/12/19
 ****************************************************************/

#include <algorithm>
#include "Player.h"

// 构造函数
Player::Player(std::string nickname) :
    name(nickname)
{
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        std::fill_n(battleMap[i], BATTLE_MAP_COLUMNS, NoChampion);
    }
    std::fill_n(waitingMap, WAITING_MAP_COUNT, NoChampion);
}