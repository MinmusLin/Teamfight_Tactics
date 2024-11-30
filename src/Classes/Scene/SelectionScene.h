/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     SelectionScene.h
 * File Function: SelectionScene类的定义
 * Author:        刘淑仪、林继申
 * Update Date:   2023/12/30
 ****************************************************************/

#pragma once
#ifndef _SELECTION_SCENE_H_
#define _SELECTION_SCENE_H_

#include "cocos2d.h"

/*
 * Class Name:     SelectionScene
 * Class Function: 选择场景类
 */
class SelectionScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 实现 SelectionScene 类的 create 方法
    CREATE_FUNC(SelectionScene);
};

#endif // !_SELECTION_SCENE_H_