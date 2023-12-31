/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     Champion.h
 * File Function: Champion类的定义
 * Author:        杨宇琨、刘淑仪、林继申
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _CHAMPION_H_
#define _CHAMPION_H_

#include "cocos2d.h"
#include "Battle/Battle.h"
#include "proj.win32/Constant.h"

// Battle 类前声明（用于解决循环依赖）
class Battle;

/*
 * Class Name:     Champion
 * Class Function: 战斗英雄类
 */
class Champion : public cocos2d::Sprite {
public:
    // 构造函数
    Champion(const ChampionCategory championCategory);

    // 绑定战斗类
    void setBattle(Battle* myBattle);

    // 设置战斗英雄所属阵营
    void setCamp(const bool isMyFlag);

    // 获取战斗英雄所属阵营
    bool getCamp() const;

    // 设置当前战斗英雄位置
    void setCurrentPosition(const int& x, const int& y);

    // 获取战斗英雄移动状态
    bool getIsMoving() const;

    // 设置战斗英雄移动状态
    void setIsMoving();

    // 重置战斗英雄移动状态
    void resetIsMoving();

    // 获取战斗英雄攻击状态
    bool getIsAttacking() const;

    // 设置战斗英雄攻击状态
    void setIsAttacking();

    // 重置战斗英雄攻击状态
    void resetIsAttacking();

    // 获取当前锁定敌人战斗英雄指针
    Champion* getCurrentEnemy() const;

    // 获取当前敌人战斗位置属性
    BattleLocation getCurrentLocation() const;

    // 获取精灵类指针
    cocos2d::Sprite* getSprite() const;

    // 获取战斗英雄属性
    ChampionAttributes getAttributes() const;

    // 获取当前目标位置
    BattleLocation getCurrentDestination() const;

    // 设置当前目标位置
    void setCurrentDestination(const BattleLocation destination);

    // 重置当前目标位置
    void resetCurrentDestination();

    // 获取攻击时间间隔
    float getAttackIntervalTimer() const;

    // 增加攻击时间间隔
    void addAttackIntervalTimer(const float delta);

    // 重置攻击时间间隔
    void resetAttackIntervalTimer();

    // 获取移动时间间隔
    float getMoveIntervalTimer() const;

    // 增加移动时间间隔
    void addMoveIntervalTimer(const float delta);

    // 重置移动时间间隔
    void resetMoveIntervalTimer();

    // 获取当前移动
    cocos2d::MoveTo* getCurrentMove() const;

    // 设置当前移动
    void setCurrentMove(cocos2d::MoveTo* move);

    // 重置当前移动
    void resetCurrentMove();

    // 获取当前战斗类指针
    Battle* getCurrentBattle() const;

    // 获取最近敌方战斗英雄
    void findNearestEnemy(const bool isMy);

    // 判断攻击范围内是否存在敌人战斗英雄
    bool isInAttackRange();

    // 判断当前位置是否在战斗区地图内
    bool isInMap(const int& x, const int& y);

    // 移动
    BattleLocation moveTowards(Champion* nearestEnemy);

    // 攻击
    void attack();

    // 技能
    void skill();

    // 死亡
    void die();

    // 设置武器是否可见
    void setSwordVisible(const bool visible);

    // 初始化武器
    void initializeSword(const cocos2d::Vec2& position);

    // 设置武器位置
    void setSwordPosition(const cocos2d::Vec2& position);

    // 获取生命条
    Sprite* getHealthBar() const;

    // 获取经验条
    Sprite* getManaBar() const;

    // 获取最大生命值
    float getMaxHealthPoints() const;

    // 获取最大经验值
    float getMaxMagicPoints() const;

    // 设置生命条
    void setHealthBar(Sprite* HealthBar);

    // 设置经验条
    void setManaBar(Sprite* ManaBar);

    // 获取武器精灵类指针
    Sprite* getSword() const;

    // 羁绊效果
    void bond();

private:
    Battle* currentBattle;             // 战斗类
    ChampionAttributes attributes;     // 战斗英雄属性
    BattleLocation currentLocation;    // 当前战斗英雄位置
    BattleLocation currentDestination; // 当前目标位置
    Champion* currentEnemy;            // 当前锁定敌人战斗英雄指针
    Sprite* sprite;                    // 精灵类指针
    Sprite* sword;                     // 武器精灵类指针
    Sprite* healthBar;                 // 生命条指针
    Sprite* manaBar;                   // 技能条指针
    cocos2d::MoveTo* currentMove;      // 当前移动
    int maxHealthPoints;               // 最大生命值
    int maxMagicPoints;                // 最大魔法值
    bool isMyFlag;                     // 战斗英雄阵营
    bool isMoving;                     // 移动状态
    bool isAttaking;                   // 攻击状态
    float attackIntervalTimer;         // 攻击时间间隔
    float moveIntervalTimer;           // 移动时间间隔

    // 受到攻击
    void beingAttack(const int& damage);

    // 计算两点间距离
    float distanceBetweenPoints(const cocos2d::Vec2& a, const cocos2d::Vec2& b);

    // 触发技能
    void triggerSkill(const int magnification, bool isCondition = true);
};

#endif // !_CHAMPION_H_