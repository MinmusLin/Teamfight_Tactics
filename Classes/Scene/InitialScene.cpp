/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     InitialScene.cpp
 * File Function: InitialScene类的实现
 * Author:        林继申
 * Update Date:   2023/12/12
 ****************************************************************/

#include "InitialScene.h"
#include "MenuScene.h"
#include "Button/HoverButton.h"
#include "ui/CocosGUI.h"
#include "proj.win32/Constant.h"
#include "GBKToUTF8.h"

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

    // 创建文本框
    auto textField = TextField::create(GBKToUTF8::getString("请在这里输入您的昵称"), "../Resources/Fonts/FZZGY_J_EB.ttf", FONT_SIZE);
    textField->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 100)); // TODO: 这里的位置通过常变量替代
    textField->setMaxLength(NICKNAME_MAX_LENGTH);
    textField->setMaxLengthEnabled(true);
    this->addChild(textField);

    // 创建标签
    auto promptLabel = Label::createWithTTF("", "../Resources/Fonts/FZZGY_J_EB.ttf", FONT_SIZE);
    promptLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 200)); // TODO: 这里的位置通过常变量替代
    this->addChild(promptLabel);

    // 为文本框添加事件监听器
    textField->addEventListener([promptLabel](Ref* sender, TextField::EventType type) {
        if (type == TextField::EventType::INSERT_TEXT || type == TextField::EventType::DELETE_BACKWARD) {
            auto textField = dynamic_cast<TextField*>(sender);
            std::string nickname = textField->getString();
            std::string text = GBKToUTF8::getString("你好！") + nickname;
            promptLabel->setString(text);
        }
        });

    // 创建按钮
    auto startButton = HoverButton::create("../Resources/Buttons/StartDefaultButton.png",
        "../Resources/Buttons/StartHoverButton.png",
        "../Resources/Buttons/StartActiveButton.png");

    // 设置按钮位置
    startButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 - 300)); // TODO: 这里的位置通过常变量替代

    // 创建一个提示
    auto nameLabel = Label::createWithTTF(GBKToUTF8::getString("请输入昵称"), "../Resources/Fonts/FZZGY_J_EB.ttf", FONT_SIZE);
    nameLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 300)); // TODO: 这里的位置通过常变量替代
    nameLabel->setVisible(false);
    this->addChild(nameLabel);

    // 为按钮添加事件处理器
    startButton->addTouchEventListener([this, textField, nameLabel](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            std::string nickname = textField->getString();
            if (!nickname.empty()) {
                UserDefault::getInstance()->setStringForKey("PlayerName", nickname);
                UserDefault::getInstance()->flush();
                Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene::createScene(), Color3B::WHITE));
            }
            else {
                nameLabel->setVisible(true);
                this->scheduleOnce([nameLabel](float dt) {nameLabel->setVisible(false); }, PROMPT_MESSAGE_DURATION, "hidePromptLabel");
            }
        }
        });

    // 将按钮添加到场景中
    this->addChild(startButton);

    return true;
}