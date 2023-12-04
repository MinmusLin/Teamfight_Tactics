/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     MenuScene.cpp
 * File Function: MenuScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/5
 ****************************************************************/

#include "MenuScene.h"
#include "Buttons/HoverButton.h"

USING_NS_CC;
using ui::Button;
using ui::Widget;

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
    offlineModeButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 200)); // TODO: �����λ��ͨ�����������
    onlineModeButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2)); // TODO: �����λ��ͨ�����������
    settingsButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 - 200)); // TODO: �����λ��ͨ�����������

    // Ϊ��ť����¼�������
    offlineModeButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::BEGAN) {
            // TODO: ��ϰģʽ�����ӿ�
        }
        });
    onlineModeButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::BEGAN) {
            // TODO: ����ģʽ�����ӿ�
        }
        });
    settingsButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::BEGAN) {
            // TODO: ���ó����ӿ�
        }
        });

    // ����ť��ӵ�������
    this->addChild(offlineModeButton);
    this->addChild(onlineModeButton);
    this->addChild(settingsButton);

    return true;
}