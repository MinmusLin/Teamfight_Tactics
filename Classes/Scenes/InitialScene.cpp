/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     InitialScene.cpp
 * File Function: InitialScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/4
 ****************************************************************/

#include "InitialScene.h"
#include "MenuScene.h"
#include "..\proj.win32\Constant.h"

USING_NS_CC;

// 创建场景
Scene* InitialScene::createScene()
{
    auto scene = Scene::create();
    auto layer = InitialScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool InitialScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    // 加载背景
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/InitialScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    this->setupKeyboardListener();

    return true;
}

// 键盘事件监听器
void InitialScene::setupKeyboardListener()
{
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(InitialScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

// 处理键盘按下事件的回调函数
void InitialScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene::createScene(), COLOR_WHITE));
}