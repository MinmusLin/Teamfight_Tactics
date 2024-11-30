/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeRuneScene.h
 * File Function: OfflineModeRuneScene类的定义
 * Author:        刘淑仪、林继申
 * Update Date:   2023/12/30
 ****************************************************************/

#pragma once
#ifndef _OFFLINE_MODE_RUNE_SCENE_
#define _OFFLINE_MODE_RUNE_SCENE_

#include "cocos2d.h"

/*
 * Class Name:     OfflineModeRuneScene
 * Class Function: 练习模式强化符文场景类
 */
class OfflineModeRuneScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 实现 OfflineModeRuneScene 类的 create 方法
    CREATE_FUNC(OfflineModeRuneScene);
};

#endif // !_OFFLINE_MODE_RUNE_SCENE_