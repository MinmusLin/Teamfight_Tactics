/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.cpp
 * File Function: OfflineModeBattleScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/20
 ****************************************************************/

#include <iostream>
#include "OfflineModeBattleScene.h"
#include "Button/HoverButton.h"
#include "Control/OfflineModeControl.h"
#include "MenuScene.h"

USING_NS_CC;

// ��ϰģʽ��Ϸ������
OfflineModeControl* s_offlineModeControl;

// ��������
Scene* OfflineModeBattleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = OfflineModeBattleScene::create();
    scene->addChild(layer);
    return scene;
}

// ��ʼ������
bool OfflineModeBattleScene::init()
{
    // ��������
    if (!Scene::init()) {
        return false;
    }
    
    // ���ر���
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OfflineModeBattleScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ������ť
    auto returnMenuButton = HoverButton::create("../Resources/Buttons/OfflineModeBattleSceneButtons/ReturnMenuDefaultButton.png",
        "../Resources/Buttons/OfflineModeBattleSceneButtons/ReturnMenuHoverButton.png",
        "../Resources/Buttons/OfflineModeBattleSceneButtons/ReturnMenuActiveButton.png");

    // ���ð�ťλ��
    returnMenuButton->setPosition(Vec2(screenSize.width / 2 + 450, screenSize.height / 2 - 100)); // TODO: ��ťλ��ͨ�����������

    // Ϊ��ť����¼�������
    returnMenuButton->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::BEGAN) {
            delete s_offlineModeControl;
            Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), Color3B::WHITE));
        }
        });

    // ����ť��ӵ�������
    this->addChild(returnMenuButton);

    // ������ϰģʽ��Ϸ������
    try {
        s_offlineModeControl = new OfflineModeControl;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        throw;
    }
    s_offlineModeControl->run(this);

    return true;
}