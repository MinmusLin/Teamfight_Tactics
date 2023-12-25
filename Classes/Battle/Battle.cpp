/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Battle.cpp
 * File Function: Battle���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/23
 ****************************************************************/

#include <iostream>
#include "Battle.h"
#include "Champion/Champion.h"

<<<<<<< Updated upstream
// ���캯��
=======
 // ���캯��
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
                // ������Ӫ
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

// ��ȡ����Ӣ����Ϣ
Champion* Battle::getChampion(const int& x, const int& y)
{
    return championMap[x][y];
}

// ��������
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

// ��ȡ�����ҷ�ʣ������
int Battle::getMyCount()
{
    return myCount;
}

// ��ȡ���ϵз�ʣ������
int Battle::getEnemyCount()
{
    return enemyCount;
}

// ���ӵз�����
void Battle::addEnemyCount()
{
    enemyCount++;
}

// �����ҷ�����
void Battle::addMyCount()
{
    myCount++;
}

// ��������
void Battle::resetCount()
{
    enemyCount = 0;
    myCount = 0;
}

// ��һ��λ���ÿ�
void Battle::setEmpty(const int& x, const int& y)
{
    championMap[x][y] = nullptr;
}

// ����һ������
void Battle::placeChampion(const int& x, const int& y, Champion* champion)
{
    championMap[x][y] = champion;
}

// ʤ��
void Battle::setWin()
{
    isWinning = win;
}

// ʧ��
void Battle::setLose()
{
    isWinning = lose;
}

// ƽ��
void Battle::setDraw()
{
    isWinning = draw;
}
