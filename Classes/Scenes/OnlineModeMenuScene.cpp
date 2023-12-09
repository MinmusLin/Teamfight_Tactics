/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeMenuScene.cpp
 * File Function: OnlineModeMenuScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/9
 ****************************************************************/

#include "OnlineModeMenuScene.h"
#include "Buttons/HoverButton.h"
#include "MenuScene.h"

USING_NS_CC;
using ui::Button;
using ui::Widget;

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
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OnlineModeMenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建按钮
    auto createRoomButton = HoverButton::create("../Resources/Buttons/CreateRoomDefaultButton.png",
        "../Resources/Buttons/CreateRoomHoverButton.png",
        "../Resources/Buttons/CreateRoomActiveButton.png");
    auto joinRoomButton = HoverButton::create("../Resources/Buttons/JoinRoomDefaultButton.png",
        "../Resources/Buttons/JoinRoomHoverButton.png",
        "../Resources/Buttons/JoinRoomActiveButton.png");
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/ReturnMenuActiveButton.png");

    // 设置按钮位置
    createRoomButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 200)); // TODO: 这里的位置通过常变量替代
    joinRoomButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2)); // TODO: 这里的位置通过常变量替代
    returnMenuButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 - 200)); // TODO: 这里的位置通过常变量替代

    // 为按钮添加事件处理器
    createRoomButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::BEGAN) {
            // TODO: 创建服务器
        }
        });
    joinRoomButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::BEGAN) {
            // TODO: 创建客户端
        }
        });
    returnMenuButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::BEGAN) {
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene::createScene(), Color3B::WHITE));
        }
        });

    // 将按钮添加到场景中
    this->addChild(createRoomButton);
    this->addChild(joinRoomButton);
    this->addChild(returnMenuButton);

    return true;
}