/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.h
 * File Function: Champion类的定义
 * Author:        林继申
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
 * Class Function: 战斗英雄类
 */
class Champion : public cocos2d::Sprite {
public:
    // 构造函数
    Champion(const ChampionCategory championCategory);

    // 绑定战斗
    void setBattle(Battle* myBattle);

    // 设置英雄所属阵营
    void setCamp(bool isMyChampion);

    // 设置当前英雄位置
    void setCurrentPosition(const int& x, const int& y);

    // 设置英雄所属阵营
    bool getCamp() const;

    // 获取英雄移动状态
    bool getIsMoving() const;

    // 获取英雄移动状态
    void setIsMoving();

    // 获取英雄移动状态
    void resetIsMoving();

    // 获取英雄移动状态
    bool getIsAttacking() const;

    // 获取英雄移动状态
    void setIsAttacking();

    // 获取英雄移动状态
    void resetIsAttacking();

    // 获取当前敌人
    Champion* getCurrentEnemy() const;

    // 获取当前敌人
    BattleLocation getCurrentLocation() const;

    // 获取精灵类指针
    cocos2d::Sprite* getSprite() const;

    // 获取战斗英雄属性
    ChampionAttributes getAttributes() const;

    // 获取攻击时间间隔
    BattleLocation Champion::getCurrentDestination() const;

    // 增加攻击时间间隔
    void Champion::setCurrentDestination(BattleLocation destination);

    // 重置攻击时间间隔
    void Champion::resetCurrentDestination();

    // 获取攻击时间间隔
    float Champion::getAttackIntervalTimer() const;

    // 增加攻击时间间隔
    void Champion::addAttackIntervalTimer(float delta);

    // 重置攻击时间间隔
    void Champion::resetAttackIntervalTimer();

    // 获取移动时间间隔
    float Champion::getMoveIntervalTimer() const;

    // 增加移动时间间隔
    void Champion::addMoveIntervalTimer(float delta);

    // 重置移动时间间隔
    void Champion::resetMoveIntervalTimer();

    // 获取当前移动
    cocos2d::MoveTo* Champion::getCurrentMove() const;

    // 设置当前移动
    void Champion::setCurrentMove(cocos2d::MoveTo* move);

    // 重置当前移动
    void Champion::resetCurrentMove();

    // 获取当前战斗
    Battle* Champion::getCurrentBattle() const;

    // 获取最近的地方英雄
    void findNearestEnemy();

    // 判断攻击范围内是否有敌人
    bool isInAttackRange();

    // 判断攻击范围内是否有敌人
    inline bool isInMap(const int& x, const int& y);

    // 移动坐标
    BattleLocation moveTowards(Champion* nearestEnemy);

    // 攻击
    void attack();

    // 技能
    void skill();

    // 死亡退出
    void Die();

    // 逐帧运行
    void update(float delta) ;


    // 在 Champion 类中创建并添加血条和蓝条
    void initHealthBar();

    // 更新血条和蓝条的位置
    void updateHealthBarPosition();

    // 更新血条和蓝条的显示
    void updateHealthBarDisplay();


private:
    ChampionAttributes attributes;     // 战斗英雄属性
    BattleLocation currentLocation;    // 战斗英雄当前位置
    BattleLocation currentDestination; // 当前目标位置
    Champion* currentEnemy;            // 当前锁定敌人
    Sprite* sprite;                    // 精灵类指针
    Sprite* healthBar;                 // 精灵类指针
    Sprite* manaBar;                   // 精灵类指针
    cocos2d::MoveTo* currentMove;      // 当前精灵移动
    Battle* currentBattle;             // 当前战斗
    int maxHealthPoints;               // 生命值
    int maxMagicPoints;                // 魔法值
    float attackIntervalTimer;         // 攻击间隔计时器
    float moveIntervalTimer;           // 移动间隔计时器
    bool isMoving;                     // 移动状态
    bool isMy;                         // 战斗英雄阵营
    bool isAttaking;                   // 战斗状态

    //计算两点距离
    float distanceBetweenPoints(const cocos2d::Vec2& p1, const cocos2d::Vec2& p2);

    // 受到攻击
    void beingAttack(const int& damage);
};

#endif // !_CHAMPION_H_