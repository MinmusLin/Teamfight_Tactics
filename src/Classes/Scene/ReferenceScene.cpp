/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     ReferenceScene.cpp
 * File Function: ReferenceScene���ʵ��
 * Author:        �����ǡ��ּ���
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#include "ReferenceScene.h"
#include "MenuScene.h"
#include "Button/HoverButton.h"
#include "proj.win32/Constant.h"
#include "proj.win32/AudioPlayer.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Vec2;

// ��������
Scene* ReferenceScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ReferenceScene::create();
    scene->addChild(layer);
    return scene;
}

// ��ʼ������
bool ReferenceScene::init()
{
    // ��������
    if (!Scene::init()) {
        return false;
    }

    // ���ر���
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/ReferenceScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ������ť
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/ReferenceSceneButtons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/ReferenceSceneButtons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/ReferenceSceneButtons/ReturnMenuActiveButton.png");
    returnMenuButton->setPosition(Vec2(screenSize.width / 2 + REFERENCE_SCENE_RETURN_MENU_BUTTON_OFFSET_X, screenSize.height / 2 + REFERENCE_SCENE_RETURN_MENU_BUTTON_OFFSET_Y));
    returnMenuButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
    this->addChild(returnMenuButton);

    return true;
}