/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     InitialScene.cpp
 * File Function: InitialScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/4
 ****************************************************************/

#include "InitialScene.h"
#include "MenuScene.h"
#include "..\proj.win32\Constant.h"

USING_NS_CC;

// ��������
Scene* InitialScene::createScene()
{
    auto scene = Scene::create();
    auto layer = InitialScene::create();
    scene->addChild(layer);
    return scene;
}

// ��ʼ������
bool InitialScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    // ���ر���
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/InitialScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    this->setupKeyboardListener();

    return true;
}

// �����¼�������
void InitialScene::setupKeyboardListener()
{
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(InitialScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

// ������̰����¼��Ļص�����
void InitialScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene::createScene(), COLOR_WHITE));
}