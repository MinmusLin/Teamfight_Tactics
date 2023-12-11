/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HeroA.h
 * File Function: HeroA类的定义
 * Author:        杨宇琨
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _HERO_A_H_
#define _HERO_A_H_

#include "Hero.h"
#include "proj.win32/Constant.h"

/*
 * Class Name:     HeroA
 * Class Function: 战斗英雄 HeroA 类
 */
class HeroA : public Hero {
public:
    // 构造函数
    HeroA() : Hero(HERO_A_ATTR) {}
};

#endif // !_HERO_A_H_