/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     MenuScene.cpp
 * File Function: MenuScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/4
 ****************************************************************/

#include "MenuScene.h"

USING_NS_CC;

// 创建场景
Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool MenuScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    // 加载背景
    auto screenSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::create("../Resources/Scenes/MenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    return true;
}