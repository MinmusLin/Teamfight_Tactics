/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.h
 * File Function: OfflineModeBattleScene类的定义
 * Author:        杨宇琨、刘淑仪、林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _OFFLINE_MODE_BATTLE_SCENE_H_
#define _OFFLINE_MODE_BATTLE_SCENE_H_

#include "cocos2d.h"
#include "Champion/Champion.h"

/*
 * Class Name:     OfflineModeBattleScene
 * Class Function: 练习模式对战场景类
 */
class OfflineModeBattleScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 每一帧被自动调用的 update 方法
    virtual void update(float delta);

    // 实现 OfflineModeBattleScene 类的 create 方法
    CREATE_FUNC(OfflineModeBattleScene);

private:
    int battleChampionCount = 0;                                                // 当前场景战斗区战斗英雄数量
    Champion* battleChampion[BATTLE_AREA_MAX_CHAMPION_COUNT * 2] = { nullptr }; // 当前场景战斗区战斗英雄指针
};

#endif // !_OFFLINE_MODE_BATTLE_SCENE_H_