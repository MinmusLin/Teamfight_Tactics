/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.cpp
 * File Function: OfflineModeBattleScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/20
 ****************************************************************/

#include <iostream>
#include "OfflineModeBattleScene.h"
#include "Button/HoverButton.h"
#include "Control/OfflineModeControl.h"
#include "MenuScene.h"

USING_NS_CC;

// 练习模式游戏控制类
OfflineModeControl* s_offlineModeControl;

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
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OfflineModeBattleScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建按钮
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/OfflineModeBattleSceneButtons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/OfflineModeBattleSceneButtons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/OfflineModeBattleSceneButtons/ReturnMenuActiveButton.png");

    // 设置按钮位置
    returnMenuButton->setPosition(Vec2(screenSize.width / 2 + 450, screenSize.height / 2 - 100)); // TODO: 按钮位置通过常变量替代

    // 为按钮添加事件处理器
    returnMenuButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::BEGAN) {
            delete s_offlineModeControl;
            Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), Color3B::WHITE));
        }
        });

    // 将按钮添加到场景中
    this->addChild(returnMenuButton);

    // 运行练习模式游戏控制类
    try {
        s_offlineModeControl = new OfflineModeControl;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        throw;
    }
    s_offlineModeControl->run(this);

    return true;
}