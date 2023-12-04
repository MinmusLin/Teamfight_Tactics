/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     MenuScene.cpp
 * File Function: MenuScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/5
 ****************************************************************/

#include "MenuScene.h"
#include "Buttons/HoverButton.h"

USING_NS_CC;
using ui::Button;
using ui::Widget;

// 创建场景
Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool MenuScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }
    
    // 加载背景
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/MenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建按钮
    auto offlineModeButton = HoverButton::create("../Resources/Buttons/OfflineModeDefaultButton.png",
        "../Resources/Buttons/OfflineModeHoverButton.png",
        "../Resources/Buttons/OfflineModeActiveButton.png");
    auto onlineModeButton = HoverButton::create("../Resources/Buttons/OnlineModeDefaultButton.png",
        "../Resources/Buttons/OnlineModeHoverButton.png",
        "../Resources/Buttons/OnlineModeActiveButton.png");
    auto settingsButton = HoverButton::create("../Resources/Buttons/SettingsDefaultButton.png",
        "../Resources/Buttons/SettingsHoverButton.png",
        "../Resources/Buttons/SettingsActiveButton.png");

    // 设置按钮位置
    offlineModeButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 200)); // TODO: 这里的位置通过常变量替代
    onlineModeButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2)); // TODO: 这里的位置通过常变量替代
    settingsButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 - 200)); // TODO: 这里的位置通过常变量替代

    // 为按钮添加事件处理器
    offlineModeButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::BEGAN) {
            // TODO: 练习模式场景接口
        }
        });
    onlineModeButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::BEGAN) {
            // TODO: 联机模式场景接口
        }
        });
    settingsButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::BEGAN) {
            // TODO: 设置场景接口
        }
        });

    // 将按钮添加到场景中
    this->addChild(offlineModeButton);
    this->addChild(onlineModeButton);
    this->addChild(settingsButton);

    return true;
}