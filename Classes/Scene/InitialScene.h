/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     InitialScene.h
 * File Function: InitialScene类的定义
 * Author:        林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _INITIAL_SCENE_H_
#define _INITIAL_SCENE_H_

#include "cocos2d.h"

/*
 * Class Name:     InitialScene
 * Class Function: 初始场景类
 */
class InitialScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 实现 InitialScene 类的 create 方法
    CREATE_FUNC(InitialScene);

private:
    // 检查字符合法性
    bool isValidCharacter(const char32_t ch);

    // 检查字符串合法性
    bool isValidString(const std::string& str);
};

#endif // !_INITIAL_SCENE_H_