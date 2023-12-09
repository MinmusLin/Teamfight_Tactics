/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OnlineModeMenuScene.cpp
 * File Function: OnlineModeMenuScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/9
 ****************************************************************/

#include "OnlineModeMenuScene.h"
#include "Buttons/HoverButton.h"
#include "MenuScene.h"

USING_NS_CC;
using ui::Button;
using ui::Widget;

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
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OnlineModeMenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ������ť
    auto createRoomButton = HoverButton::create("../Resources/Buttons/CreateRoomDefaultButton.png",
        "../Resources/Buttons/CreateRoomHoverButton.png",
        "../Resources/Buttons/CreateRoomActiveButton.png");
    auto joinRoomButton = HoverButton::create("../Resources/Buttons/JoinRoomDefaultButton.png",
        "../Resources/Buttons/JoinRoomHoverButton.png",
        "../Resources/Buttons/JoinRoomActiveButton.png");
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/ReturnMenuActiveButton.png");

    // ���ð�ťλ��
    createRoomButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 200)); // TODO: �����λ��ͨ�����������
    joinRoomButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2)); // TODO: �����λ��ͨ�����������
    returnMenuButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 - 200)); // TODO: �����λ��ͨ�����������

    // Ϊ��ť����¼�������
    createRoomButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::BEGAN) {
            // TODO: ����������
        }
        });
    joinRoomButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::BEGAN) {
            // TODO: �����ͻ���
        }
        });
    returnMenuButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::BEGAN) {
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene::createScene(), Color3B::WHITE));
        }
        });

    // ����ť��ӵ�������
    this->addChild(createRoomButton);
    this->addChild(joinRoomButton);
    this->addChild(returnMenuButton);

    return true;
}