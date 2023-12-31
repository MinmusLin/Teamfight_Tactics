/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     PreferenceScene.cpp
 * File Function: PreferenceScene类的实现
 * Author:        刘淑仪、林继申
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#include "PreferenceScene.h"
#include "MenuScene.h"
#include "Button/HoverButton.h"
#include "proj.win32/Constant.h"
#include "proj.win32/AudioPlayer.h"

// 命名空间
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Vec2;

// 创建场景
Scene* PreferenceScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PreferenceScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool PreferenceScene::init()
{
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/PreferenceScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建按钮
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/PreferenceSceneButtons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/PreferenceSceneButtons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/PreferenceSceneButtons/ReturnMenuActiveButton.png");
    returnMenuButton->setPosition(Vec2(screenSize.width / 2 + PREFERENCE_SCENE_RETURN_MENU_BUTTON_OFFSET_X, screenSize.height / 2 + PREFERENCE_SCENE_RETURN_MENU_BUTTON_OFFSET_Y));
    returnMenuButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // 加载点击音效
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    this->addChild(returnMenuButton);

    return true;
}