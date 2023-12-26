/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Player.cpp
 * File Function: Player类的实现
 * Author:        林继申
 * Update Date:   2023/12/25
 ****************************************************************/

#include <algorithm>
#include "Player.h"

// 构造函数
Player::Player(const std::string nickname) :
    name(nickname),
    healthPoints(INITIAL_HEALTH_POINTS)
{
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        std::fill_n(battleMap[i], BATTLE_MAP_COLUMNS, NoChampion);
    }
    std::fill_n(waitingMap, WAITING_MAP_COUNT, NoChampion);
}

// 获取战斗区地图
void Player::getBattleMap(ChampionCategory(*&battleMap)[BATTLE_MAP_COLUMNS])
{
    battleMap = this->battleMap;
}

// 减少玩家生命值
void Player::decreaseHealthPoints(const int num)
{
    healthPoints -= num;
    if (healthPoints <= 0) {
        healthPoints = 0;
    }
}

// 获取玩家生命值
int Player::getHealthPoints() const
{
    return healthPoints;
}

// 获取玩家昵称
std::string Player::getPlayerName() const
{
    return name;
}