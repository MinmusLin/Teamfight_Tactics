/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PreferenceScene.h
 * File Function: PreferenceScene类的定义
 * Author:        刘淑仪、林继申
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _PREFERENCE_SCENE_H_
#define _PREFERENCE_SCENE_H_

#include "cocos2d.h"

/*
 * Class Name:     PreferenceScene
 * Class Function: 玩法场景类
 */
class PreferenceScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 实现 PreferenceScene 类的 create 方法
    CREATE_FUNC(PreferenceScene);
};

#endif // !_PREFERENCE_SCENE_H_