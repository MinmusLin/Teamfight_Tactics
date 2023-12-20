/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Player.h
 * File Function: Player��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/20
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
    Player(std::string nickname);

    // ��ȡս������ͼ
    ChampionCategory** getBattleMap() const;

protected:
    std::string name;                                                // ����ǳ�
    ChampionCategory battleMap[BATTLE_MAP_ROWS][BATTLE_MAP_COLUMNS]; // ս������ͼ
    ChampionCategory waitingMap[WAITING_MAP_COUNT];                  // ��ս����ͼ
};

#endif // !_PLAYER_H_