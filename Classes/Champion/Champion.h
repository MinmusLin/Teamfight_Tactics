/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.h
 * File Function: Champion��Ķ���
 * Author:        ���������ּ���
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _CHAMPION_H_
#define _CHAMPION_H_

#include <string>
#include "proj.win32/Constant.h"

/*
 * Class Name:     Champion
 * Class Function: ս��Ӣ����
 */
class Champion {
public:
    // ���캯��
    Champion(const ChampionAttributes& attributes);

private:
    ChampionAttributes attrs; // ս��Ӣ������
};

#endif // !_CHAMPION_H_