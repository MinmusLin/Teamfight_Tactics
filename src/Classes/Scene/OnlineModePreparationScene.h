/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModePreparationScene.h
 * File Function: OnlineModePreparationScene类的定义
 * Author:        林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _ONLINE_MODE_PREPARATION_SCENE_H_
#define _ONLINE_MODE_PREPARATION_SCENE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

/*
 * Class Name:     OnlineModePreparationScene
 * Class Function: 联机模式准备场景类
 */
class OnlineModePreparationScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 当场景重新进入时调用
    void onEnter();

    // 实现 OnlineModePreparationScene 类的 create 方法
    CREATE_FUNC(OnlineModePreparationScene);

private:
    // 设置进度条更新逻辑与计时器
    void setScheduleOnce(cocos2d::ui::LoadingBar* progressBar, cocos2d::Label* progressLabel);
};

#endif // !_ONLINE_MODE_PREPARATION_SCENE_H_