/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Hero.h
 * File Function: Hero��Ķ���
 * Author:        �ּ��ꡢ������
 * Update Date:   2023/12/12
 ****************************************************************/

#pragma once
#ifndef _HERO_H_
#define _HERO_H_

#include <string>
#include "proj.win32/Constant.h"

/*
 * Class Name:     Hero
 * Class Function: ս��Ӣ����
 */
class Hero {
public:
    // ���캯��
    Hero(const HeroAttributes& attrs) :
        heroName(attrs.heroName),
        heroImage(attrs.heroImage),
        healthPoints(attrs.healthPoints),
        experiencePoints(attrs.experiencePoints),
        attackDamage(attrs.attackDamage),
        skillDamage(attrs.skillDamage),
        skillTriggerThreshold(attrs.skillTriggerThreshold),
        attackSpeed(attrs.attackSpeed),
        movementSpeed(attrs.movementSpeed),
        defenseCoefficient(attrs.defenseCoefficient) {}

private:
    std::string heroName;      // ս��Ӣ������
    std::string heroImage;     // ս��Ӣ��ͼƬ·��
    int healthPoints;          // ����ֵ
    int experiencePoints;      // ����ֵ
    int attackDamage;          // �����˺�
    int skillDamage;           // �����˺�
    int skillTriggerThreshold; // ���ܴ�����ֵ
    float attackSpeed;         // �����ٶ�
    float movementSpeed;       // �ƶ��ٶ�
    float defenseCoefficient;  // ����ϵ��
};

#endif // !_HERO_H_