/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     MenuScene.h
 * File Function: MenuScene类的定义
 * Author:        林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "cocos2d.h"

/*
 * Class Name:     MenuScene
 * Class Function: 菜单场景类
 */
class MenuScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 实现 MenuScene 类的 create 方法
    CREATE_FUNC(MenuScene);
};

#endif // !_MENU_SCENE_H_