/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     MenuScene.cpp
 * File Function: MenuScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/19
 ****************************************************************/

#include <chrono>
#include "MenuScene.h"
#include "Button/HoverButton.h"
#include "OnlineModeMenuScene.h"
#include "OfflineModeBattleScene.h"
#include "GBKToUTF8.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

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
    offlineModeButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_BUTTONS_OFFSET_X, screenSize.height / 2 + MENU_SCENE_OFFLINE_MODE_BUTTON_OFFSET_Y));
    onlineModeButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_BUTTONS_OFFSET_X, screenSize.height / 2 + MENU_SCENE_ONLINE_MODE_BUTTON_OFFSET_Y));
    settingsButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_BUTTONS_OFFSET_X, screenSize.height / 2 + MENU_SCENE_SETTINGS_BUTTON_OFFSET_Y));

    // 为按钮添加事件处理器
    offlineModeButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::BEGAN) {
            Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, OfflineModeBattleScene::createScene(), Color3B::WHITE));
        }
        });
    onlineModeButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::BEGAN) {
            Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, OnlineModeMenuScene::createScene(), Color3B::WHITE));
        }
        });
    settingsButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::BEGAN) {
            // TODO: 设置场景接口
        }
        });

    // 将按钮添加到场景中
    this->addChild(offlineModeButton);
    this->addChild(onlineModeButton);
    this->addChild(settingsButton);

    // 获取当前时间
    std::time_t now_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const int hour = std::localtime(&now_c)->tm_hour;

    // 根据小时数决定欢迎提示语
    std::string greeting;
    if (hour < 6) {
        greeting = "，凌晨好！";
    }
    else if (hour < 9) {
        greeting = "，早上好！";
    }
    else if (hour < 12) {
        greeting = "，上午好！";
    }
    else if (hour < 14) {
        greeting = "，中午好！";
    }
    else if (hour < 18) {
        greeting = "，下午好！";
    }
    else {
        greeting = "，晚上好！";
    }

    // 创建一个欢迎提示
    auto welcomeLabel = Label::createWithTTF(UserDefault::getInstance()->getStringForKey("PlayerName") + GBKToUTF8::getString(greeting), "../Resources/Fonts/FZZGY_J_EB.ttf", MENU_SCENE_FONT_SIZE);
    welcomeLabel->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_BUTTONS_OFFSET_X, screenSize.height / 2 + MENU_SCENE_WELCOME_LABLE_OFFSET_Y));
    welcomeLabel->setTextColor(Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(welcomeLabel);

    return true;
}