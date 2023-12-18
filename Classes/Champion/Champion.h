/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.h
 * File Function: Champion类的定义
 * Author:        林继申
 * Update Date:   2023/12/19
 ****************************************************************/

#pragma once
#ifndef _CHAMPION_H_
#define _CHAMPION_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"

/*
 * Class Name:     Champion
 * Class Function: 战斗英雄类
 */
class Champion : public cocos2d::Sprite {
public:
    // 构造函数
    Champion(ChampionCategory championCategory);

    // 获取精灵类指针
    cocos2d::Sprite* getSprite() const;

    // 获取战斗英雄属性
    ChampionAttributes getAttributes() const;

private:
    Sprite* sprite;           // 精灵类指针
    ChampionAttributes attrs; // 战斗英雄属性
};

#endif // !_CHAMPION_H_