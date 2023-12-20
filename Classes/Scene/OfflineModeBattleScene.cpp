/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     OfflineModeBattleScene.cpp
 * File Function: OfflineModeBattleScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/20
 ****************************************************************/

#include "Control/OfflineModeControl.h"
#include "OfflineModeBattleScene.h"

USING_NS_CC;

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
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/OfflineModeBattleScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ���ü�ʱ��
    this->scheduleOnce([](float dt) {
        Director::getInstance()->popScene();
        }, 2, "PopOfflineModeBattleScene");

    return true;
}