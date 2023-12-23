/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.cpp
 * File Function: OfflineModeBattleScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/24
 ****************************************************************/

#include "Control/OfflineModeControl.h"
#include "OfflineModeBattleScene.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Vec2;

// ��ϰģʽ��Ϸ������
extern OfflineModeControl* g_offlineModeControl;

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
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OfflineModeBattleScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ���ü�ʱ��
    this->scheduleOnce([](float dt) {
        cocos2d::Director::getInstance()->popScene();
        }, 2, "PopOfflineModeBattleScene");

    return true;
}