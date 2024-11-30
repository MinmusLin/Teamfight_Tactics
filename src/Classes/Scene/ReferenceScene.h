/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ReferenceScene.h
 * File Function: ReferenceScene类的定义
 * Author:        刘淑仪、林继申
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _REFERENCE_SCENE_H_
#define _REFERENCE_SCENE_H_

#include "cocos2d.h"

/*
 * Class Name:     ReferenceScene
 * Class Function: 玩法场景类
 */
class ReferenceScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 实现 ReferenceScene 类的 create 方法
    CREATE_FUNC(ReferenceScene);
};

#endif // !_REFERENCE_SCENE_H_