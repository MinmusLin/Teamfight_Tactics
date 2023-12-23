/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeMenuScene.cpp
 * File Function: OnlineModeMenuScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/24
 ****************************************************************/

#include "OnlineModeMenuScene.h"
#include "Button/HoverButton.h"
#include "MenuScene.h"
#include "proj.win32/Constant.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Vec2;

// ��������
Scene* OnlineModeMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OnlineModeMenuScene::create();
    scene->addChild(layer);
    return scene;
}

// ��ʼ������
bool OnlineModeMenuScene::init()
{
    // ��������
    if (!Scene::init()) {
        return false;
    }
    
    // ���ر���
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OnlineModeMenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ������ť
    auto createRoomButton = HoverButton::create("../Resources/Buttons/OnlineModeMenuSceneButtons/CreateRoomDefaultButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/CreateRoomHoverButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/CreateRoomActiveButton.png");
    auto joinRoomButton = HoverButton::create("../Resources/Buttons/OnlineModeMenuSceneButtons/JoinRoomDefaultButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/JoinRoomHoverButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/JoinRoomActiveButton.png");
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/OnlineModeMenuSceneButtons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/OnlineModeMenuSceneButtons/ReturnMenuActiveButton.png");

    // ���ð�ťλ��
    createRoomButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 200)); // TODO: ��ťλ��ͨ�����������
    joinRoomButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2)); // TODO: ��ťλ��ͨ�����������
    returnMenuButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 - 200)); // TODO: ��ťλ��ͨ�����������

    // Ϊ��ť����¼�������
    createRoomButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // TODO: ���������������ӿ�
        }
        });
    joinRoomButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            // TODO: �����ͻ��˳����ӿ�
        }
        });
    returnMenuButton->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });

    // ����ť��ӵ�������
    this->addChild(createRoomButton);
    this->addChild(joinRoomButton);
    this->addChild(returnMenuButton);

    return true;
}