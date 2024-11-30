/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     SelectionScene.h
 * File Function: SelectionScene类的实现
 * Author:        刘淑仪、林继申
 * Update Date:   2023/12/31
 ****************************************************************/

#include "SelectionScene.h"
#include "MenuScene.h"
#include "Button/HoverButton.h"
#include "proj.win32/Constant.h"
#include "proj.win32/AudioPlayer.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// 小小英雄种类
int g_littleChampionCategory = DEFAULT_LITTLE_CHAMPION_CATEGORY;

// 玩家昵称
extern std::string g_PlayerName;

// 创建场景
Scene* SelectionScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SelectionScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool SelectionScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/SelectionScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建标签
    auto promptLabel = Label::createWithTTF(g_PlayerName + u8"，请选择你的小小英雄!", "../Resources/Fonts/DingDingJinBuTi.ttf", SELECTION_SCENE_LABEL_FONT_SIZE);
    promptLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + SELECTION_SCENE_LABEL_OFFSET_Y));
    promptLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(promptLabel);

    // 创建小小英雄按钮
    for (int i = 0; i < MAX_LITTLE_CHAMPION_COUNT; i++) {
        auto littleChampion = HoverButton::create(static_cast<std::string>("../Resources/Buttons/SelectionSceneButtons/LittleChampion") + std::to_string(i + 1) + static_cast<std::string>("DefaultButton.png"),
            static_cast<std::string>("../Resources/Buttons/SelectionSceneButtons/LittleChampion") + std::to_string(i + 1) + static_cast<std::string>("HoverButton.png"),
            static_cast<std::string>("../Resources/Buttons/SelectionSceneButtons/LittleChampion") + std::to_string(i + 1) + static_cast<std::string>("ActiveButton.png"));
        littleChampion->setPosition(Vec2(screenSize.width / 2 + SELECTION_SCENE_BUTTON_OFFSET_X + (i % (MAX_LITTLE_CHAMPION_COUNT / 2)) * SELECTION_SCENE_BUTTON_HORIZONTAL_INTERVAL,
            screenSize.height / 2 + SELECTION_SCENE_BUTTON_OFFSET_Y + (i / (MAX_LITTLE_CHAMPION_COUNT / 2)) * SELECTION_SCENE_BUTTON_VERTICAL_INTERVAL));
        littleChampion->addTouchEventListener([i](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
                // 加载点击音效
                audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

                g_littleChampionCategory = i + 1;
                cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
            }
            });
        this->addChild(littleChampion);
    }

    return true;
}