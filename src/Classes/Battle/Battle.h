/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Battle.h
 * File Function: Battle��Ķ���
 * Author:        ���������ּ���
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _BATTLE_H_
#define _BATTLE_H_

#include <vector>
#include "Champion/Champion.h"
#include "proj.win32/Constant.h"

// Champion ��ǰ���������ڽ��ѭ��������
class Champion;

/*
 * Class Name:     Battle
 * Class Function: ��ս��
 */
class Battle {
public:
    // ���캯��
    Battle(const ChampionCategory myFlagMap[][BATTLE_MAP_COLUMNS], const ChampionCategory enemyFlagMap[][BATTLE_MAP_COLUMNS]);

    // ��������
    ~Battle();

    // ��ȡս��Ӣ��ָ��
    Champion* getChampion(const int& x, const int& y);

    // ��ȡ�ҷ�ս��Ӣ������
    int getMyCount();

    // ��ȡ�з�ս��Ӣ������
    int getEnemyCount();

    // �����ҷ�ս��Ӣ������
    void addMyCount();

    // ���ӵз�ս��Ӣ������
    void addEnemyCount();

    // ����ս��Ӣ������
    void resetCount();

    // �Ƴ�ս��Ӣ��
    void setEmpty(const int& x, const int& y);

    // ����ս��Ӣ��
    void placeChampion(const int& x, const int& y, Champion* champion);

    // ����ս��ʤ��״̬
    void setBattleSituation(const BattleSituation battleSituation);

    // ��ȡ�ҷ��Ч��
    std::vector<int> getMyBond() const;

    // ��ȡ�з��Ч��
    std::vector<int> getEnemyBond() const;

    // �Ч��
    void bondEffect(const Bond bond, const bool isMyFlag);

    // ������Ԫ��
    friend class Champion;

private:
    ChampionCategory championCategoryMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS]; // ս������ͼ
    Champion* championMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS];                // ս����ս��Ӣ��ָ��
    int myCount;                                                               // �ҷ�ս��Ӣ������
    int enemyCount;                                                            // �з�ս��Ӣ������
    BattleSituation battleSituation;                                           // ս��ʤ��״̬
    std::vector<int> myBond;                                                   // �ҷ��Ч��
    std::vector<int> enemyBond;                                                // �з��Ч��
};

#endif // !_BATTLE_H_