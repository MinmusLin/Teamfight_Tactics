/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeRuneScene.h
 * File Function: OfflineModeRuneScene类的实现
 * Author:        刘淑仪、林继申
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
    const auto background = Sprite::create("../Resources/Scenes/OfflineModeRuneScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建天赋符文按钮
    const std::string talentRune[] = { "Pirate", "General", "Warriors" };
    const int offsetX[] = { -TALENT_RUNE_BUTTON_OFFSET_X, 0, TALENT_RUNE_BUTTON_OFFSET_X };
    HoverButton* talentRuneButton[TALENT_RUNE_COUNT] = { nullptr };
    for (int i = 0; i < TALENT_RUNE_COUNT; i++) {
        talentRuneButton[i] = HoverButton::create(static_cast<std::string>("../Resources/Buttons/OfflineModeRuneSceneButtons/") + talentRune[i] + static_cast<std::string>("RuneDefaultButton.png"),
            static_cast<std::string>("../Resources/Buttons/OfflineModeRuneSceneButtons/") + talentRune[i] + static_cast<std::string>("RuneHoverButton.png"),
            static_cast<std::string>("../Resources/Buttons/OfflineModeRuneSceneButtons/") + talentRune[i] + static_cast<std::string>("RuneActiveButton.png"));
        talentRuneButton[i]->setPosition(Vec2(screenSize.width / 2 + offsetX[i], screenSize.height / 2 + TALENT_RUNE_BUTTON_OFFSET_Y));
        talentRuneButton[i]->addTouchEventListener([i](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
                cocos2d::UserDefault::getInstance()->setIntegerForKey("TalentRune", i);
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
        this->addChild(talentRuneButton[i]);
    }

    return true;
}