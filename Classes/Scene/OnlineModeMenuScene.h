/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeMenuScene.h
 * File Function: OnlineModeMenuScene类的定义
 * Author:        林继申
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _ONLINE_MODE_MENU_SCENE_H_
#define _ONLINE_MODE_MENU_SCENE_H_

#include "cocos2d.h"

/*
 * Class Name:     OnlineModeMenuScene
 * Class Function: 联机模式菜单场景类
 */
class OnlineModeMenuScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 实现 OnlineModeMenuScene 类的 create 方法
    CREATE_FUNC(OnlineModeMenuScene);

private:
    // 服务器 IPv4 地址合法性检验
    bool isValidIPv4(const std::string& str);

    // 服务器端口合法性检验
    bool isValidPort(const std::string& str);
};

#endif // !_ONLINE_MODE_MENU_SCENE_H_