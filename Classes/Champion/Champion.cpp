/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.cpp
 * File Function: Champion类的实现
 * Author:        林继申
 * Update Date:   2023/12/23
 ****************************************************************/

#include "Champion.h"

// 构造函数
Champion::Champion(const ChampionCategory championCategory) :
    attributes(CHAMPION_ATTR_MAP.at(championCategory))
{
    sprite = Sprite::create(attributes.championImagePath);
}

// 获取精灵类指针
cocos2d::Sprite* Champion::getSprite() const
{
    return sprite;
}

// 获取战斗英雄属性
ChampionAttributes Champion::getAttributes() const
{
    return attributes;
}