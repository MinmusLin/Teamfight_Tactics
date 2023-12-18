/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.h
 * File Function: Champion��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/19
 ****************************************************************/

#pragma once
#ifndef _CHAMPION_H_
#define _CHAMPION_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"

/*
 * Class Name:     Champion
 * Class Function: ս��Ӣ����
 */
class Champion : public cocos2d::Sprite {
public:
    // ���캯��
    Champion(ChampionCategory championCategory);

    // ��ȡ������ָ��
    cocos2d::Sprite* getSprite() const;

    // ��ȡս��Ӣ������
    ChampionAttributes getAttributes() const;

private:
    Sprite* sprite;           // ������ָ��
    ChampionAttributes attrs; // ս��Ӣ������
};

#endif // !_CHAMPION_H_