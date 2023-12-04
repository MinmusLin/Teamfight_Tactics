/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     InitialScene.cpp
 * File Function: InitialScene���ʵ��
 * Author:        �ּ���
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

    // ������ť
    auto startButton = HoverButton::create("../Resources/Buttons/StartDefaultButton.png",
        "../Resources/Buttons/StartHoverButton.png",
        "../Resources/Buttons/StartActiveButton.png");

    // ���ð�ťλ��
    startButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 - 300));

    // Ϊ��ť����¼�������
    startButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene::createScene(), Color3B::WHITE));
        });

    // ����ť��ӵ�������
    this->addChild(startButton);

    // �����ı���
    auto textField = TextField::create("Enter Your Nickname Here", "../Resources/Fonts/FZZGY_J_EB.ttf", 24);
    textField->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 100));
    this->addChild(textField);

    // ������ǩ
    auto label = Label::createWithSystemFont("��ã�", "../Resources/Fonts/FZZGY_J_EB.ttf", 24);
    label->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 150));
    this->addChild(label);

    // Ϊ�ı�������¼�������
    textField->addEventListener([label](Ref* sender, TextField::EventType type) {
        if (type == TextField::EventType::INSERT_TEXT || type == TextField::EventType::DELETE_BACKWARD) {
            auto textField = dynamic_cast<TextField*>(sender);
            std::string text = "��ã�" + textField->getString() + "��";
            label->setString(text);
        }
        });

    return true;
}