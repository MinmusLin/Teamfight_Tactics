/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     MenuScene.cpp
 * File Function: MenuScene类的实现
 * Author:        林继申、刘淑仪
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#include <chrono>
#include "MenuScene.h"
#include "ReferenceScene.h"
#include "Button/HoverButton.h"
#include "OnlineModeMenuScene.h"
#include "OfflineModeRuneScene.h"
#include "proj.win32/Constant.h"
#include "SettingsScene.h"
#include "proj.win32/AudioPlayer.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// 玩家昵称
extern std::string g_PlayerName;

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

    // 设置默认天赋符文
    cocos2d::UserDefault::getInstance()->setIntegerForKey("TalentRune", static_cast<int>(NoTalentRune));

    // 加载音乐
    audioPlayer("../Resources/Music/MenuScene_DarkSideOfPower.mp3", true);

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/MenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建按钮
    auto offlineModeButton = HoverButton::create("../Resources/Buttons/MenuSceneButtons/OfflineModeDefaultButton.png",
        "../Resources/Buttons/MenuSceneButtons/OfflineModeHoverButton.png",
        "../Resources/Buttons/MenuSceneButtons/OfflineModeActiveButton.png");
    auto onlineModeButton = HoverButton::create("../Resources/Buttons/MenuSceneButtons/OnlineModeDefaultButton.png",
        "../Resources/Buttons/MenuSceneButtons/OnlineModeHoverButton.png",
        "../Resources/Buttons/MenuSceneButtons/OnlineModeActiveButton.png");
    auto settingsButton = HoverButton::create("../Resources/Buttons/MenuSceneButtons/SettingsDefaultButton.png",
        "../Resources/Buttons/MenuSceneButtons/SettingsHoverButton.png",
        "../Resources/Buttons/MenuSceneButtons/SettingsActiveButton.png");
    auto referenceButton = HoverButton::create("../Resources/Buttons/MenuSceneButtons/ReferenceDefaultButton.png",
        "../Resources/Buttons/MenuSceneButtons/ReferenceHoverButton.png",
        "../Resources/Buttons/MenuSceneButtons/ReferenceActiveButton.png");
    auto exitGameButton = HoverButton::create("../Resources/Buttons/MenuSceneButtons/ExitGameDefaultButton.png",
        "../Resources/Buttons/MenuSceneButtons/ExitGameHoverButton.png",
        "../Resources/Buttons/MenuSceneButtons/ExitGameActiveButton.png");

    // 设置按钮位置
    offlineModeButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_BUTTONS_OFFSET_X, screenSize.height / 2 + MENU_SCENE_OFFLINE_MODE_BUTTON_OFFSET_Y));
    onlineModeButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_BUTTONS_OFFSET_X, screenSize.height / 2 + MENU_SCENE_ONLINE_MODE_BUTTON_OFFSET_Y));
    settingsButton->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_BUTTONS_OFFSET_X, screenSize.height / 2 + MENU_SCENE_SETTINGS_BUTTON_OFFSET_Y));
    referenceButton->setPosition(Vec2(screenSize.width - MENU_SCENE_REFERENCE_BUTTON_OFFSET_X, MENU_SCENE_REFERENCE_BUTTON_OFFSET_Y));
    exitGameButton->setPosition(Vec2(screenSize.width - MENU_SCENE_EXIT_GAME_BUTTON_OFFSET_X, MENU_SCENE_EXIT_GAME_BUTTON_OFFSET_Y));

    // 为按钮添加事件处理器
    offlineModeButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, OfflineModeRuneScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    onlineModeButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, OnlineModeMenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    settingsButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, SettingsScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    referenceButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, ReferenceScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    exitGameButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            cocos2d::Director::getInstance()->end();
        }
        });

    // 将按钮添加到场景中
    this->addChild(offlineModeButton);
    this->addChild(onlineModeButton);
    this->addChild(settingsButton);
    this->addChild(referenceButton);
    this->addChild(exitGameButton);

    // 创建一个欢迎提示
    const std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    const int number = (rand() % 100 < RANDOM_WELCOME_PROMPT_PROBABILITY * 100) ? std::localtime(&now)->tm_hour : rand() % RANDOM_PROMPT_COUNT + 24;
    auto welcomeLabel = Label::createWithTTF(g_PlayerName + WELCOME_PROMPT.at(number), "../Resources/Fonts/DingDingJinBuTi.ttf", MENU_SCENE_FONT_SIZE);
    welcomeLabel->setPosition(Vec2(screenSize.width / 2 + MENU_SCENE_BUTTONS_OFFSET_X, screenSize.height / 2 + MENU_SCENE_WELCOME_LABEL_OFFSET_Y));
    welcomeLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(welcomeLabel);

    return true;
}