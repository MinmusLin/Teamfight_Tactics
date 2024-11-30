/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.h
 * File Function: Champion��Ķ���
 * Author:        �������������ǡ��ּ���
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _CHAMPION_H_
#define _CHAMPION_H_

#include "cocos2d.h"
#include "Battle/Battle.h"
#include "proj.win32/Constant.h"

// Battle ��ǰ���������ڽ��ѭ��������
class Battle;

/*
 * Class Name:     Champion
 * Class Function: ս��Ӣ����
 */
class Champion : public cocos2d::Sprite {
public:
    // ���캯��
    Champion(const ChampionCategory championCategory);

    // ��ս����
    void setBattle(Battle* myBattle);

    // ����ս��Ӣ��������Ӫ
    void setCamp(const bool isMyFlag);

    // ��ȡս��Ӣ��������Ӫ
    bool getCamp() const;

    // ���õ�ǰս��Ӣ��λ��
    void setCurrentPosition(const int& x, const int& y);

    // ��ȡս��Ӣ���ƶ�״̬
    bool getIsMoving() const;

    // ����ս��Ӣ���ƶ�״̬
    void setIsMoving();

    // ����ս��Ӣ���ƶ�״̬
    void resetIsMoving();

    // ��ȡս��Ӣ�۹���״̬
    bool getIsAttacking() const;

    // ����ս��Ӣ�۹���״̬
    void setIsAttacking();

    // ����ս��Ӣ�۹���״̬
    void resetIsAttacking();

    // ��ȡ��ǰ��������ս��Ӣ��ָ��
    Champion* getCurrentEnemy() const;

    // ��ȡ��ǰ����ս��λ������
    BattleLocation getCurrentLocation() const;

    // ��ȡ������ָ��
    cocos2d::Sprite* getSprite() const;

    // ��ȡս��Ӣ������
    ChampionAttributes getAttributes() const;

    // ��ȡ��ǰĿ��λ��
    BattleLocation getCurrentDestination() const;

    // ���õ�ǰĿ��λ��
    void setCurrentDestination(const BattleLocation destination);

    // ���õ�ǰĿ��λ��
    void resetCurrentDestination();

    // ��ȡ����ʱ����
    float getAttackIntervalTimer() const;

    // ���ӹ���ʱ����
    void addAttackIntervalTimer(const float delta);

    // ���ù���ʱ����
    void resetAttackIntervalTimer();

    // ��ȡ�ƶ�ʱ����
    float getMoveIntervalTimer() const;

    // �����ƶ�ʱ����
    void addMoveIntervalTimer(const float delta);

    // �����ƶ�ʱ����
    void resetMoveIntervalTimer();

    // ��ȡ��ǰ�ƶ�
    cocos2d::MoveTo* getCurrentMove() const;

    // ���õ�ǰ�ƶ�
    void setCurrentMove(cocos2d::MoveTo* move);

    // ���õ�ǰ�ƶ�
    void resetCurrentMove();

    // ��ȡ��ǰս����ָ��
    Battle* getCurrentBattle() const;

    // ��ȡ����з�ս��Ӣ��
    void findNearestEnemy(const bool isMy);

    // �жϹ�����Χ���Ƿ���ڵ���ս��Ӣ��
    bool isInAttackRange();

    // �жϵ�ǰλ���Ƿ���ս������ͼ��
    bool isInMap(const int& x, const int& y);

    // �ƶ�
    BattleLocation moveTowards(Champion* nearestEnemy);

    // ����
    void attack();

    // ����
    void skill();

    // ����
    void die();

    // ���������Ƿ�ɼ�
    void setSwordVisible(const bool visible);

    // ��ʼ������
    void initializeSword(const cocos2d::Vec2& position);

    // ��������λ��
    void setSwordPosition(const cocos2d::Vec2& position);

    // ��ȡ������
    Sprite* getHealthBar() const;

    // ��ȡ������
    Sprite* getManaBar() const;

    // ��ȡ�������ֵ
    float getMaxHealthPoints() const;

    // ��ȡ�����ֵ
    float getMaxMagicPoints() const;

    // ����������
    void setHealthBar(Sprite* HealthBar);

    // ���þ�����
    void setManaBar(Sprite* ManaBar);

    // ��ȡ����������ָ��
    Sprite* getSword() const;

    // �Ч��
    void bond();

private:
    Battle* currentBattle;             // ս����
    ChampionAttributes attributes;     // ս��Ӣ������
    BattleLocation currentLocation;    // ��ǰս��Ӣ��λ��
    BattleLocation currentDestination; // ��ǰĿ��λ��
    Champion* currentEnemy;            // ��ǰ��������ս��Ӣ��ָ��
    Sprite* sprite;                    // ������ָ��
    Sprite* sword;                     // ����������ָ��
    Sprite* healthBar;                 // ������ָ��
    Sprite* manaBar;                   // ������ָ��
    cocos2d::MoveTo* currentMove;      // ��ǰ�ƶ�
    int maxHealthPoints;               // �������ֵ
    int maxMagicPoints;                // ���ħ��ֵ
    bool isMyFlag;                     // ս��Ӣ����Ӫ
    bool isMoving;                     // �ƶ�״̬
    bool isAttaking;                   // ����״̬
    float attackIntervalTimer;         // ����ʱ����
    float moveIntervalTimer;           // �ƶ�ʱ����

    // �ܵ�����
    void beingAttack(const int& damage);

    // ������������
    float distanceBetweenPoints(const cocos2d::Vec2& a, const cocos2d::Vec2& b);

    // ��������
    void triggerSkill(const int magnification, bool isCondition = true);
};

#endif // !_CHAMPION_H_