/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     MenuScene.cpp
 * File Function: MenuScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/4
 ****************************************************************/

#include "MenuScene.h"

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
    if (!Scene::init()) {
        return false;
    }
    
    // ���ر���
    auto screenSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::create("../Resources/Scenes/MenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    return true;
}