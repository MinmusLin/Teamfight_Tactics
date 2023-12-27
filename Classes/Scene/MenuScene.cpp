/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     MenuScene.cpp
 * File Function: MenuScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/27
 * License:       MIT License
 ****************************************************************/

#include <iostream>
#include <chrono>
#include "MenuScene.h"
#include "Button/HoverButton.h"
#include "OnlineModeMenuScene.h"
#include "OfflineModePreparationScene.h"
#include "Control/OfflineModeControl.h"
#include "GBKToUTF8/GBKToUTF8.h"
#include "proj.win32/Constant.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// ��ϰģʽ��Ϸ������
OfflineModeControl* g_offlineModeControl = nullptr;

// ��������
Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

// ��ʼ������
bool MenuScene::init()
{
    // ��������
    if (!Scene::init()) {
        return false;
    }
    
    // ���ر���
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/MenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ������ť
    auto offlineModeButton = HoverButton::create("../Resources/Buttons/MenuSceneButtons/OfflineModeDefaultButton.png",
        "../Resources/Buttons/MenuSceneButtons/OfflineModeHoverButton.png",
        "../Resources/Buttons/MenuSceneButtons/OfflineModeActiveButton.png");
    auto onlineModeButton = HoverButton::create("../Resources/Buttons/MenuSceneButtons/OnlineModeDefaultButton.png",
        "../Resources/Buttons/MenuSceneButtons/OnlineModeHoverButton.png",
        "../Resources/Buttons/MenuSceneButtons/OnlineModeActiveButton.png");
    auto settingsButton = HoverButton::create("../Resources/Buttons/MenuSceneButtons/SettingsDefaultButton.png",
        "../Resources/Buttons/MenuSceneButtons/SettingsHoverButton.png",
        "../Resources/Buttons/MenuSceneButtons/SettingsActiveButton.png");

    // ���ð�ťλ��
    offlineModeButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_BUTTONS_OFFSET_X, screenSize.height / 2 + MENU_SCENE_OFFLINE_MODE_BUTTON_OFFSET_Y));
    onlineModeButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_BUTTONS_OFFSET_X, screenSize.height / 2 + MENU_SCENE_ONLINE_MODE_BUTTON_OFFSET_Y));
    settingsButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_BUTTONS_OFFSET_X, screenSize.height / 2 + MENU_SCENE_SETTINGS_BUTTON_OFFSET_Y));

    // Ϊ��ť����¼�������
    offlineModeButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            try {
                g_offlineModeControl = new OfflineModeControl;
            }
            catch (const std::bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                throw;
            }
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, OfflineModePreparationScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    onlineModeButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, OnlineModeMenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    settingsButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // TODO: ���ó����ӿ�
        }
        });

    // ����ť��ӵ�������
    this->addChild(offlineModeButton);
    this->addChild(onlineModeButton);
    this->addChild(settingsButton);

    // ����һ����ӭ��ʾ
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const int number = (rand() % 100 < RANDOM_WELCOME_PROMPT_PROBABILITY * 100) ? std::localtime(&now)->tm_hour : rand() % 24 + 24;
    auto welcomeLabel = Label::createWithTTF(cocos2d::UserDefault::getInstance()->getStringForKey("PlayerName") + GBKToUTF8::getString(WELCOME_PROMPT.at(number)), "../Resources/Fonts/FangZhengZhaoGeYuan.ttf", MENU_SCENE_FONT_SIZE);
    welcomeLabel->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_BUTTONS_OFFSET_X, screenSize.height / 2 + MENU_SCENE_WELCOME_LABEL_OFFSET_Y));
    welcomeLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(welcomeLabel);

    return true;
}