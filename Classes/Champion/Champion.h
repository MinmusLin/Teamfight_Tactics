/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.h
 * File Function: Champion类的定义
 * Author:        杨宇琨、林继申
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _CHAMPION_H_
#define _CHAMPION_H_

#include <string>
#include "proj.win32/Constant.h"

/*
 * Class Name:     Champion
 * Class Function: 战斗英雄类
 */
class Champion {
public:
    // 构造函数
    Champion(const ChampionAttributes& attributes);

private:
    ChampionAttributes attrs; // 战斗英雄属性
};

#endif // !_CHAMPION_H_