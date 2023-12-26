/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Player.cpp
 * File Function: Player���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/25
 ****************************************************************/

#include <algorithm>
#include "Player.h"

// ���캯��
Player::Player(const std::string nickname) :
    name(nickname),
    healthPoints(INITIAL_HEALTH_POINTS)
{
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        std::fill_n(battleMap[i], BATTLE_MAP_COLUMNS, NoChampion);
    }
    std::fill_n(waitingMap, WAITING_MAP_COUNT, NoChampion);
}

// ��ȡս������ͼ
void Player::getBattleMap(ChampionCategory(*&battleMap)[BATTLE_MAP_COLUMNS])
{
    battleMap = this->battleMap;
}

// �����������ֵ
void Player::decreaseHealthPoints(const int num)
{
    healthPoints -= num;
    if (healthPoints <= 0) {
        healthPoints = 0;
    }
}

// ��ȡ�������ֵ
int Player::getHealthPoints() const
{
    return healthPoints;
}

// ��ȡ����ǳ�
std::string Player::getPlayerName() const
{
    return name;
}