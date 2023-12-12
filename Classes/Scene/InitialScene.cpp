/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     InitialScene.cpp
 * File Function: InitialScene���ʵ��
 * Author:        �ּ���
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
    // ��������
    if (!Scene::init()) {
        return false;
    }

    // ���ر���
    const auto screenSize = Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/InitialScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // �����ı���
    auto textField = TextField::create(GBKToUTF8::getString("�����������������ǳ�"), "../Resources/Fonts/FZZGY_J_EB.ttf", FONT_SIZE);
    textField->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 100)); // TODO: �����λ��ͨ�����������
    textField->setMaxLength(NICKNAME_MAX_LENGTH);
    textField->setMaxLengthEnabled(true);
    this->addChild(textField);

    // ������ǩ
    auto promptLabel = Label::createWithTTF("", "../Resources/Fonts/FZZGY_J_EB.ttf", FONT_SIZE);
    promptLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 200)); // TODO: �����λ��ͨ�����������
    this->addChild(promptLabel);

    // Ϊ�ı�������¼�������
    textField->addEventListener([promptLabel](Ref* sender, TextField::EventType type) {
        if (type == TextField::EventType::INSERT_TEXT || type == TextField::EventType::DELETE_BACKWARD) {
            auto textField = dynamic_cast<TextField*>(sender);
            std::string nickname = textField->getString();
            std::string text = GBKToUTF8::getString("��ã�") + nickname;
            promptLabel->setString(text);
        }
        });

    // ������ť
    auto startButton = HoverButton::create("../Resources/Buttons/StartDefaultButton.png",
        "../Resources/Buttons/StartHoverButton.png",
        "../Resources/Buttons/StartActiveButton.png");

    // ���ð�ťλ��
    startButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 - 300)); // TODO: �����λ��ͨ�����������

    // ����һ����ʾ
    auto nameLabel = Label::createWithTTF(GBKToUTF8::getString("�������ǳ�"), "../Resources/Fonts/FZZGY_J_EB.ttf", FONT_SIZE);
    nameLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 300)); // TODO: �����λ��ͨ�����������
    nameLabel->setVisible(false);
    this->addChild(nameLabel);

    // Ϊ��ť����¼�������
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

    // ����ť��ӵ�������
    this->addChild(startButton);

    return true;
}