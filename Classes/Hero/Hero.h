/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Hero.h
 * File Function: Hero类的定义
 * Author:        林继申
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _HERO_H_
#define _HERO_H_

#include <string>
#include "proj.win32/Constant.h"

/*
 * Class Name:     Hero
 * Class Function: 战斗英雄类
 */
class Hero {
public:
    // 构造函数
    Hero(const HeroAttributes& attrs);

private:
    std::string heroName;      // 战斗英雄名称
    std::string heroImage;     // 战斗英雄图片路径
    int healthPoints;          // 生命值
    int experiencePoints;      // 经验值
    int attackDamage;          // 攻击伤害
    int skillDamage;           // 技能伤害
    int skillTriggerThreshold; // 技能触发阈值
    float attackSpeed;         // 攻击速度
    float movementSpeed;       // 移动速度
    float defenseCoefficient;  // 防御系数
};

#endif // !_HERO_H_