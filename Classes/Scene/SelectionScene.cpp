/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     SelectionScene.h
 * File Function: SelectionScene���ʵ��
 * Author:        ������
 * Update Date:   2023/12/29
 ****************************************************************/

#include "SelectionScene.h"
#include "MenuScene.h"
#include "Button/HoverButton.h"
#include "GBKToUTF8/GBKToUTF8.h"
#include "proj.win32/Constant.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// ��������
Scene* SelectionScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SelectionScene::create();
    scene->addChild(layer);
    return scene;
}

// ��ʼ������
bool SelectionScene::init()
{
    // ��������
    if (!Scene::init()) {
        return false;
    }

    // ���ر���
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/SelectionScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // ����ССӢ�۰�ť
    for (int i = 0; i < MAX_LITTLE_CHAMPION_COUNT; i++) {
        auto littleChampion = HoverButton::create(static_cast<std::string>("../Resources/Buttons/SelectionSceneButtons/LittleChampion") + std::to_string(i + 1) + static_cast<std::string>("DefaultButton.png"),
            static_cast<std::string>("../Resources/Buttons/SelectionSceneButtons/LittleChampion") + std::to_string(i + 1) + static_cast<std::string>("HoverButton.png"),
            static_cast<std::string>("../Resources/Buttons/SelectionSceneButtons/LittleChampion") + std::to_string(i + 1) + static_cast<std::string>("ActiveButton.png"));
        littleChampion->setPosition(Vec2(screenSize.width / 2 + SELECTION_SCENE_LITTLE_CHAMPION_BUTTON_OFFSET_X + (i % (MAX_LITTLE_CHAMPION_COUNT / 2)) * SELECTION_SCENE_LITTLE_CHAMPION_BUTTON_DELTA_X,
            screenSize.height / 2 + SELECTION_SCENE_LITTLE_CHAMPION_BUTTON_OFFSET_Y + (i / (MAX_LITTLE_CHAMPION_COUNT / 2)) * SELECTION_SCENE_LITTLE_CHAMPION_BUTTON_DELTA_Y));
        littleChampion->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
                // TODO : ����ССӢ��
                cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), cocos2d::Color3B::WHITE));
            }
            });
        this->addChild(littleChampion);
    }

    return true;
}