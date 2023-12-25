/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.h
 * File Function: OfflineModeBattleScene类的定义
 * Author:        杨宇琨、林继申
 * Update Date:   2023/12/25
 ****************************************************************/

#pragma once
#ifndef _OFFLINE_MODE_BATTLE_SCENE_H_
#define _OFFLINE_MODE_BATTLE_SCENE_H_

#include "cocos2d.h"

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
};

#endif // !_OFFLINE_MODE_BATTLE_SCENE_H_