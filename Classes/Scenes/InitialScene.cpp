/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     InitialScene.cpp
 * File Function: InitialScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/4
 ****************************************************************/

#include "InitialScene.h"
#include "MenuScene.h"
#include "Buttons/HoverButton.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using ui::Button;
using ui::Widget;
using ui::TextField;

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
    // 创建场景
    if (!Scene::init()) {
        return false;
    }

    // 加载背景
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/InitialScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // 创建按钮
    auto startButton = HoverButton::create("../Resources/Buttons/StartDefaultButton.png",
        "../Resources/Buttons/StartHoverButton.png",
        "../Resources/Buttons/StartActiveButton.png");

    // 设置按钮位置
    startButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 - 300));

    // 为按钮添加事件处理器
    startButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene::createScene(), Color3B::WHITE));
        });

    // 将按钮添加到场景中
    this->addChild(startButton);

    // 创建文本框
    auto textField = TextField::create("Enter Your Nickname Here", "../Resources/Fonts/FZZGY_J_EB.ttf", 24);
    textField->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 100));
    this->addChild(textField);

    // 创建标签
    auto label = Label::createWithSystemFont("你好！", "../Resources/Fonts/FZZGY_J_EB.ttf", 24);
    label->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 150));
    this->addChild(label);

    // 为文本框添加事件监听器
    textField->addEventListener([label](Ref* sender, TextField::EventType type) {
        if (type == TextField::EventType::INSERT_TEXT || type == TextField::EventType::DELETE_BACKWARD) {
            auto textField = dynamic_cast<TextField*>(sender);
            std::string text = "你好，" + textField->getString() + "！";
            label->setString(text);
        }
        });

    return true;
}