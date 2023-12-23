/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeMenuScene.cpp
 * File Function: OnlineModeMenuScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/24
 ****************************************************************/

#include "OnlineModeMenuScene.h"
#include "Button/HoverButton.h"
#include "MenuScene.h"
#include "proj.win32/Constant.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Vec2;

// 创建场景
Scene* OnlineModeMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OnlineModeMenuScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool OnlineModeMenuScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }
    
    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OnlineModeMenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建按钮
    auto createRoomButton = HoverButton::create("../Resources/Buttons/OnlineModeMenuSceneButtons/CreateRoomDefaultButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/CreateRoomHoverButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/CreateRoomActiveButton.png");
    auto joinRoomButton = HoverButton::create("../Resources/Buttons/OnlineModeMenuSceneButtons/JoinRoomDefaultButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/JoinRoomHoverButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/JoinRoomActiveButton.png");
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/OnlineModeMenuSceneButtons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/ReturnMenuActiveButton.png");

    // 设置按钮位置
    createRoomButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 200)); // TODO: 按钮位置通过常变量替代
    joinRoomButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2)); // TODO: 按钮位置通过常变量替代
    returnMenuButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 - 200)); // TODO: 按钮位置通过常变量替代

    // 为按钮添加事件处理器
    createRoomButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // TODO: 创建服务器场景接口
        }
        });
    joinRoomButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // TODO: 创建客户端场景接口
        }
        });
    returnMenuButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });

    // 将按钮添加到场景中
    this->addChild(createRoomButton);
    this->addChild(joinRoomButton);
    this->addChild(returnMenuButton);

    return true;
}