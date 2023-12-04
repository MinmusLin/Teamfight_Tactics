/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     InitialScene.h
 * File Function: InitialScene类的定义
 * Author:        林继申
 * Update Date:   2023/12/4
 ****************************************************************/

#pragma once
#ifndef _INITIAL_SCENE_H_
#define _INITIAL_SCENE_H_

#include "cocos2d.h"

/*
 * Class Name:     InitialScene
 * Class Function: 初始场景
 */
class InitialScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 实现 InitialScene 类的 create 方法
    CREATE_FUNC(InitialScene);
};

#endif // !_INITIAL_SCENE_H_