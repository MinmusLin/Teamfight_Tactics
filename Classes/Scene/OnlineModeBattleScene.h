/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeBattleScene.h
 * File Function: OnlineModeBattleScene类的定义
 * Author:        杨宇琨、刘淑仪、林继申
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _ONLINE_MODE_BATTLE_SCENE_H_
#define _ONLINE_MODE_BATTLE_SCENE_H_

#include <atomic>
#include "cocos2d.h"
#include "Champion/Champion.h"

/*
 * Class Name:     OnlineModeBattleScene
 * Class Function: 联机模式对战场景类
 */
class OnlineModeBattleScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 每一帧被自动调用的 update 方法
    virtual void update(float delta);

    // 实现 OnlineModeBattleScene 类的 create 方法
    CREATE_FUNC(OnlineModeBattleScene);

private:
    int battleChampionCount = 0;                                                // 当前场景战斗区战斗英雄数量
    Champion* battleChampion[BATTLE_AREA_MAX_CHAMPION_COUNT * 2] = { nullptr }; // 当前场景战斗区战斗英雄指针
    std::atomic<bool> isServerMessageProcessed{ false };                        // 敌人玩家战斗区地图信息接收标志

    // 服务器消息监听
    void serverMessageListener();
};

#endif // !_ONLINE_MODE_BATTLE_SCENE_H_