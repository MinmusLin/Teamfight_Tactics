/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Player.h
 * File Function: Player��Ķ���
 * Author:        �ּ��ꡢ������
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "proj.win32/Constant.h"

/*
 * Class Name:     Player
 * Class Function: �����
 */
class Player {
public:
    // ���캯��
    Player(const std::string nickname);

    // ��ȡս������ͼ
    void getBattleMap(ChampionCategory(*&battleMap)[BATTLE_MAP_COLUMNS]);

    // �����������ֵ
    void decreaseHealthPoints(const int num);

    // ��ȡ�������ֵ
    int getHealthPoints() const;

    // ��ȡ����ǳ�
    std::string getPlayerName() const;

protected:
    std::string name;                                               // ����ǳ�
    ChampionCategory battleMap[PLACE_MAP_ROWS][BATTLE_MAP_COLUMNS]; // ս������ͼ
    ChampionCategory waitingMap[WAITING_MAP_COUNT];                 // ��ս����ͼ
    std::map<ChampionCategory, int> champions;                      // ս��Ӣ��������������ֵ��
    int healthPoints;                                               // �������ֵ

    // ��ȡ�����
    int getRandom(const int n) const;

    // ��ȡ��ǰ���Ʒ���
    int getStageScore() const;

    // ������ǰ����
    BattleStage evaluateStage(int stageScore) const;

    // ͳ�Ƹ���ս��Ӣ������
    std::map<ChampionCategory, int> countChampionCategories() const;

    // Ϊ�ض�ս���׶����ѡ��ս��Ӣ��
    ChampionCategory selectRandomChampion(const BattleStage stage) const;
};

#endif // !_PLAYER_H_