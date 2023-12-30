/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Battle.cpp
 * File Function: Battle���ʵ��
 * Author:        ���������ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#include <iostream>
#include "Battle.h"

// ���캯��
Battle::Battle(const ChampionCategory myFlagMap[][BATTLE_MAP_COLUMNS], const ChampionCategory enemyFlagMap[][BATTLE_MAP_COLUMNS]) :
    enemyCount(0),
    myCount(0),
    battleSituation(Draw)
{
    for (int i = 0; i < MAX_BOND_COUNT; i++) {
        myBond.push_back(0);
        enemyBond.push_back(0);
    }
    for (int i = 0; i < PLACE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            championCategoryMap[i][j] = myFlagMap[i][j];
            championCategoryMap[BATTLE_MAP_ROWS - 1 - i][BATTLE_MAP_COLUMNS - 1 - j] = enemyFlagMap[i][j];
        }
    }
    for (int i = 0; i < BATTLE_MAP_ROWS; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            if (championCategoryMap[i][j] != NoChampion) {
                // ����ս��Ӣ��
                try {
                    championMap[i][j] = new Champion(championCategoryMap[i][j]);
                }
                catch (const std::bad_alloc& e) {
                    std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                    throw;
                }
                championMap[i][j]->setCurrentPosition(i, j);

                // ����ս��Ӣ����Ӫ
                if (i < PLACE_MAP_ROWS) {
                    myCount++;
                    championMap[i][j]->setCamp(true);
                    myBond[championMap[i][j]->getAttributes().bond]++;
                }
                else {
                    enemyCount++;
                    championMap[i][j]->setCamp(false);
                    enemyBond[championMap[i][j]->getAttributes().bond]++;
                }
            }
            else {
                championMap[i][j] = nullptr;
            }
        }
    }
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

// ��ȡս��Ӣ��ָ��
Champion* Battle::getChampion(const int& x, const int& y)
{
    return championMap[x][y];
}

// ��ȡ�ҷ�ս��Ӣ������
int Battle::getMyCount()
{
    return myCount;
}

// ��ȡ�з�ս��Ӣ������
int Battle::getEnemyCount()
{
    return enemyCount;
}

// �����ҷ�ս��Ӣ������
void Battle::addMyCount()
{
    myCount++;
}

// ���ӵз�ս��Ӣ������
void Battle::addEnemyCount()
{
    enemyCount++;
}

// ����ս��Ӣ������
void Battle::resetCount()
{
    myCount = 0;
    enemyCount = 0;
}

// �Ƴ�ս��Ӣ��
void Battle::setEmpty(const int& x, const int& y)
{
    championMap[x][y] = nullptr;
}

// ����ս��Ӣ��
void Battle::placeChampion(const int& x, const int& y, Champion* champion)
{
    championMap[x][y] = champion;
}

// ����ս��ʤ��״̬
void Battle::setBattleSituation(const BattleSituation battleSituation)
{
    this->battleSituation = battleSituation;
}

// ��ȡ�ҷ��Ч��
std::vector<int> Battle::getMyBond() const
{
    return myBond;
}

// ��ȡ�з��Ч��
std::vector<int> Battle::getEnemyBond() const
{
    return enemyBond;
}

// �Ч��
void Battle::bondEffect(const Bond bond, const bool isMyFlag)
{
    if (bond == NoBond) {
        return;
    }
    int startRow = isMyFlag ? 0 : PLACE_MAP_ROWS;
    int endRow = isMyFlag ? PLACE_MAP_ROWS : BATTLE_MAP_ROWS;
    for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < BATTLE_MAP_COLUMNS; j++) {
            Champion* champion = championMap[i][j];
            if (champion && champion->getAttributes().bond == bond) {
                champion->bond();
            }
        }
    }
}