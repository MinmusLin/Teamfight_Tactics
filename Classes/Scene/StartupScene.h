/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     StartupScene.h
 * File Function: StartupScene类的定义
 * Author:        林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _STARTUP_SCENE_H_
#define _STARTUP_SCENE_H_

#include "cocos2d.h"

/*
 * Class Name:     StartupScene
 * Class Function: 启动场景类
 */
class StartupScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 实现 StartupScene 类的 create 方法
    CREATE_FUNC(StartupScene);
};

#endif // !_STARTUP_SCENE_H_