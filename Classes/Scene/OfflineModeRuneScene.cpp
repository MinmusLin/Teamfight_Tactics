/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeRuneScene.h
 * File Function: OfflineModeRuneScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/30
 ****************************************************************/

#include <iostream>
#include "OfflineModeRuneScene.h"
#include "Control/OfflineModeControl.h"
#include "OfflineModePreparationScene.h"
#include "Button/HoverButton.h"
#include "proj.win32/Constant.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Vec2;

// 练习模式游戏控制类
OfflineModeControl* g_offlineModeControl = nullptr;

// 创建场景
Scene* OfflineModeRuneScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OfflineModeRuneScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool OfflineModeRuneScene::init()
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

    // 创建强化符文按钮
    for (int i = 0; i < 1; i++) {
        auto littleChampion = HoverButton::create(static_cast<std::string>("../Resources/Buttons/SelectionSceneButtons/LittleChampion") + std::to_string(i + 1) + static_cast<std::string>("DefaultButton.png"),
            static_cast<std::string>("../Resources/Buttons/SelectionSceneButtons/LittleChampion") + std::to_string(i + 1) + static_cast<std::string>("HoverButton.png"),
            static_cast<std::string>("../Resources/Buttons/SelectionSceneButtons/LittleChampion") + std::to_string(i + 1) + static_cast<std::string>("ActiveButton.png"));
        littleChampion->setPosition(Vec2(screenSize.width / 2 + SELECTION_SCENE_BUTTON_OFFSET_X + (i % (MAX_LITTLE_CHAMPION_COUNT / 2)) * SELECTION_SCENE_BUTTON_HORIZONTAL_INTERVAL,
            screenSize.height / 2 + SELECTION_SCENE_BUTTON_OFFSET_Y + (i / (MAX_LITTLE_CHAMPION_COUNT / 2)) * SELECTION_SCENE_BUTTON_VERTICAL_INTERVAL));
        littleChampion->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
                try {
                    g_offlineModeControl = new OfflineModeControl;
                }
                catch (const std::bad_alloc& e) {
                    std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                    throw;
                }
                cocos2d::Director::getInstance()->replaceScene(OfflineModePreparationScene::createScene());
            }
            });
        this->addChild(littleChampion);
    }

    return true;
}