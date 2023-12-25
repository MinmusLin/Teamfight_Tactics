/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Battle.h
 * File Function: Battle��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/23
 ****************************************************************/

#pragma once
#ifndef _BATTLE_H_
#define _BATTLE_H_

#include "Champion/Champion.h"
#include "proj.win32/Constant.h"
#include "Champion/Champion.h"

class Champion;

/*
 * Class Name:     Battle
 * Class Function: ��ս��
 */
class Battle {
    friend class Champion;
public:
    // ���캯��
    Battle(const ChampionCategory myFlagMap[][BATTLE_MAP_COLUMNS], const ChampionCategory enemyFlagMap[][BATTLE_MAP_COLUMNS]);
<<<<<<< Updated upstream
=======

    // ��ȡ����Ӣ����Ϣ
    Champion* getChampion(const int& x, const int& y);

    // ��ȡ�����ҷ�ʣ������
    int getMyCount();

    // ��ȡ���ϵз�ʣ������
    int getEnemyCount();

    // ���ӵз�����
    void addEnemyCount();

    // �����ҷ�����
    void addMyCount();

    // ��������
    void resetCount();

    // ��һ��λ���ÿ�
    void setEmpty(const int& x, const int& y);

    // ����һ������
    void placeChampion(const int& x, const int& y,Champion* champion);

    // ʤ��
    void setWin();

    // ʧ��
    void setLose();

    // ƽ��
    void setDraw();
>>>>>>> Stashed changes

    // ��������
    ~Battle();

private:
    ChampionCategory championCategoryMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS]; // ս��Ӣ�۵�ͼ
    Champion* championMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS];                // ս��Ӣ��ָ��
    int myCount ;                                                              // �ҷ�Ӣ������
    int enemyCount ;                                                           // �з�Ӣ������
    int isWinning;                                                            // �Ƿ�ʤ��
};

#endif // !_BATTLE_H_