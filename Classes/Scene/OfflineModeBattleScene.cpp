/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.cpp
 * File Function: OfflineModeBattleScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/24
 ****************************************************************/

#include "Control/OfflineModeControl.h"
#include "OfflineModeBattleScene.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Vec2;

// 练习模式游戏控制类
extern OfflineModeControl* g_offlineModeControl;

// 创建场景
Scene* OfflineModeBattleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OfflineModeBattleScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool OfflineModeBattleScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OfflineModeBattleScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 设置计时器
    this->scheduleOnce([](float dt) {
        cocos2d::Director::getInstance()->popScene();
        }, 2, "PopOfflineModeBattleScene");

    return true;
}