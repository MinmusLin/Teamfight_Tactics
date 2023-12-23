/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.cpp
 * File Function: Champion���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/23
 ****************************************************************/

#include "Champion.h"

// ���캯��
Champion::Champion(const ChampionCategory championCategory) :
    attributes(CHAMPION_ATTR_MAP.at(championCategory))
{
    sprite = Sprite::create(attributes.championImagePath);
}

// ��ȡ������ָ��
cocos2d::Sprite* Champion::getSprite() const
{
    return sprite;
}

// ��ȡս��Ӣ������
ChampionAttributes Champion::getAttributes() const
{
    return attributes;
}