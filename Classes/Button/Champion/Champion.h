/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.h
 * File Function: Champion��Ķ���
 * Author:        �ּ���
 * Update Date:   2023/12/20
 ****************************************************************/

#pragma once
#ifndef _CHAMPION_H_
#define _CHAMPION_H_

#include "cocos2d.h"
#include "Battle/Battle.h"
#include "proj.win32/Constant.h"

class Battle;

/*
 * Class Name:     Champion
 * Class Function: ս��Ӣ����
 */
class Champion : public cocos2d::Sprite {
public:
    // ���캯��
    Champion(const ChampionCategory championCategory);

    // ��ս��
    void setBattle(Battle* myBattle);

    // ����Ӣ��������Ӫ
    void setCamp(bool isMyChampion);

    // ���õ�ǰӢ��λ��
    void setCurrentPosition(const int& x, const int& y);

    // ����Ӣ��������Ӫ
    bool getCamp() const;

    // ��ȡӢ���ƶ�״̬
    bool getIsMoving() const;

    // ��ȡӢ���ƶ�״̬
    void setIsMoving();

    // ��ȡӢ���ƶ�״̬
    void resetIsMoving();

    // ��ȡӢ���ƶ�״̬
    bool getIsAttacking() const;

    // ��ȡӢ���ƶ�״̬
    void setIsAttacking();

    // ��ȡӢ���ƶ�״̬
    void resetIsAttacking();

    // ��ȡ��ǰ����
    Champion* getCurrentEnemy() const;

    // ��ȡ��ǰ����
    BattleLocation getCurrentLocation() const;

    // ��ȡ������ָ��
    cocos2d::Sprite* getSprite() const;

    // ��ȡս��Ӣ������
    ChampionAttributes getAttributes() const;

    // ��ȡ����ʱ����
    BattleLocation Champion::getCurrentDestination() const;

    // ���ӹ���ʱ����
    void Champion::setCurrentDestination(BattleLocation destination);

    // ���ù���ʱ����
    void Champion::resetCurrentDestination();

    // ��ȡ����ʱ����
    float Champion::getAttackIntervalTimer() const;

    // ���ӹ���ʱ����
    void Champion::addAttackIntervalTimer(float delta);

    // ���ù���ʱ����
    void Champion::resetAttackIntervalTimer();

    // ��ȡ�ƶ�ʱ����
    float Champion::getMoveIntervalTimer() const;

    // �����ƶ�ʱ����
    void Champion::addMoveIntervalTimer(float delta);

    // �����ƶ�ʱ����
    void Champion::resetMoveIntervalTimer();

    // ��ȡ��ǰ�ƶ�
    cocos2d::MoveTo* Champion::getCurrentMove() const;

    // ���õ�ǰ�ƶ�
    void Champion::setCurrentMove(cocos2d::MoveTo* move);

    // ���õ�ǰ�ƶ�
    void Champion::resetCurrentMove();

    // ��ȡ��ǰս��
    Battle* Champion::getCurrentBattle() const;

    // ��ȡ����ĵط�Ӣ��
    void findNearestEnemy();

    // �жϹ�����Χ���Ƿ��е���
    bool isInAttackRange();

    // �жϹ�����Χ���Ƿ��е���
    inline bool isInMap(const int& x, const int& y);

    // �ƶ�����
    BattleLocation moveTowards(Champion* nearestEnemy);

    // ����
    void attack();

    // ����
    void skill();

    // �����˳�
    void Die();

    // ��֡����
    void update(float delta) ;


    // �� Champion ���д��������Ѫ��������
    void initHealthBar();

    // ����Ѫ����������λ��
    void updateHealthBarPosition();

    // ����Ѫ������������ʾ
    void updateHealthBarDisplay();


private:
    ChampionAttributes attributes;     // ս��Ӣ������
    BattleLocation currentLocation;    // ս��Ӣ�۵�ǰλ��
    BattleLocation currentDestination; // ��ǰĿ��λ��
    Champion* currentEnemy;            // ��ǰ��������
    Sprite* sprite;                    // ������ָ��
    Sprite* healthBar;                 // ������ָ��
    Sprite* manaBar;                   // ������ָ��
    cocos2d::MoveTo* currentMove;      // ��ǰ�����ƶ�
    Battle* currentBattle;             // ��ǰս��
    int maxHealthPoints;               // ����ֵ
    int maxMagicPoints;                // ħ��ֵ
    float attackIntervalTimer;         // ���������ʱ��
    float moveIntervalTimer;           // �ƶ������ʱ��
    bool isMoving;                     // �ƶ�״̬
    bool isMy;                         // ս��Ӣ����Ӫ
    bool isAttaking;                   // ս��״̬

    //�����������
    float distanceBetweenPoints(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2);

    // �ܵ�����
    void beingAttack(const int& damage);
};

#endif // !_CHAMPION_H_