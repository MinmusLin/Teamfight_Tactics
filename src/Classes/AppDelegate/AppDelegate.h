/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     AppDelegate.h
 * File Function: AppDelegate类的定义
 * Author:        林继申
 * Update Date:   2023/12/30
 * License:       MIT License
 ****************************************************************/

#pragma once
#ifndef _APP_DELEGATE_H_
#define _APP_DELEGATE_H_

#include "cocos2d.h"

/*
 * Class Name:     AppDelegate
 * Class Function: Cocos2d-x 应用程序类
 */
class AppDelegate : private cocos2d::Application {
public:
    // 析构函数
    virtual ~AppDelegate();

    // 初始化 OpenGL 上下文属性
    virtual void initGLContextAttrs();

    // 当应用程序完成启动并准备进入主循环时调用此函数
    virtual bool applicationDidFinishLaunching();

    // 当应用程序进入后台时调用此函数
    virtual void applicationDidEnterBackground();

    // 当应用程序从后台返回到前台时调用此函数
    virtual void applicationWillEnterForeground();
};

#endif // !_APP_DELEGATE_H_