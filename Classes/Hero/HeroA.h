/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     HeroA.h
 * File Function: HeroA��Ķ���
 * Author:        ������
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _HERO_A_H_
#define _HERO_A_H_

#include "Hero.h"
#include "proj.win32/Constant.h"

/*
 * Class Name:     HeroA
 * Class Function: ս��Ӣ�� HeroA ��
 */
class HeroA : public Hero {
public:
    // ���캯��
    HeroA() : Hero(HERO_A_ATTR) {}
};

#endif // !_HERO_A_H_