/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.cpp
 * File Function: Champion���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/19
 ****************************************************************/

#include "Champion.h"

// ���캯��
Champion::Champion(ChampionCategory championCategory) :
    attrs(CHAMPION_ATTR_MAP.at(championCategory))
{
    sprite = Sprite::create(attrs.championImagePath);
}

// ��ȡ������ָ��
cocos2d::Sprite* Champion::getSprite() const
{
    return sprite;
}

// ��ȡս��Ӣ������
ChampionAttributes Champion::getAttributes() const
{
    return attrs;
}