/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     MenuScene.cpp
 * File Function: MenuScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/19
 ****************************************************************/

#include "MenuScene.h"
#include "Button/HoverButton.h"
#include "OnlineModeMenuScene.h"
#include "OfflineModeBattleScene.h"
#include "proj.win32/Constant.h"

USING_NS_CC;

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
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/MenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ������ť
    auto offlineModeButton = HoverButton::create("../Resources/Buttons/OfflineModeDefaultButton.png",
        "../Resources/Buttons/OfflineModeHoverButton.png",
        "../Resources/Buttons/OfflineModeActiveButton.png");
    auto onlineModeButton = HoverButton::create("../Resources/Buttons/OnlineModeDefaultButton.png",
        "../Resources/Buttons/OnlineModeHoverButton.png",
        "../Resources/Buttons/OnlineModeActiveButton.png");
    auto settingsButton = HoverButton::create("../Resources/Buttons/SettingsDefaultButton.png",
        "../Resources/Buttons/SettingsHoverButton.png",
        "../Resources/Buttons/SettingsActiveButton.png");

    // ���ð�ťλ��
    offlineModeButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 200)); // TODO: ��ťλ��ͨ�����������
    onlineModeButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2)); // TODO: ��ťλ��ͨ�����������
    settingsButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 - 200)); // TODO: ��ťλ��ͨ�����������

    // Ϊ��ť����¼�������
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
            // TODO: ���ó����ӿ�
        }
        });

    // ����ť��ӵ�������
    this->addChild(offlineModeButton);
    this->addChild(onlineModeButton);
    this->addChild(settingsButton);

    return true;
}