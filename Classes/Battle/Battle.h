/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Battle.h
 * File Function: Battle��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/20
 ****************************************************************/

#pragma once
#ifndef _BATTLE_H_
#define _BATTLE_H_

#include "Champion/Champion.h"
#include "proj.win32/Constant.h"

/*
 * Class Name:     Battle
 * Class Function: ��ս��
 */
class Battle {
public:
    // ���캯��
    Battle(ChampionCategory myFlagMap[][BATTLE_MAP_COLUMNS], ChampionCategory enemyFlagMap[][BATTLE_MAP_COLUMNS]);

    // ��������
    ~Battle();

private:
    ChampionCategory championCategoryMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS]; // ս��Ӣ�۵�ͼ
    Champion* championMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS];                // ս��Ӣ��ָ��
};

#endif // !_BATTLE_H_