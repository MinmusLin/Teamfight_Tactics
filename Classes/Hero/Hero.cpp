/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Hero.cpp
 * File Function: Hero���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/12
 ****************************************************************/

#include "Hero.h"

// ���캯��
Hero::Hero(const HeroAttributes& attrs) :
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