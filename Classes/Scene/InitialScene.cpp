/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     InitialScene.cpp
 * File Function: InitialScene���ʵ��
 * Author:        �ּ���
 * Update Date:   2023/12/19
 ****************************************************************/

#include "InitialScene.h"
#include "MenuScene.h"
#include "Button/HoverButton.h"
#include "GBKToUTF8.h"
#include "proj.win32/Constant.h"

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
    auto textField = ui::TextField::create(GBKToUTF8::getString("������������Ϸ�ǳ�"), "../Resources/Fonts/FZZGY_J_EB.ttf", INITIAL_SCENE_FONT_SIZE);
    textField->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABLES_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_TEXTFIELD_OFFSET_Y));
    textField->setMaxLength(NICKNAME_MAX_LENGTH);
    textField->setMaxLengthEnabled(true);
    textField->setTextColor(Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(textField);

    // ������ǩ
    auto promptLabel = Label::createWithTTF("", "../Resources/Fonts/FZZGY_J_EB.ttf", INITIAL_SCENE_FONT_SIZE);
    promptLabel->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABLES_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_PROMPT_LABLE_OFFSET_Y));
    promptLabel->setTextColor(Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(promptLabel);

    // Ϊ�ı�������¼�������
    textField->addEventListener([promptLabel](Ref* sender, ui::TextField::EventType type) {
        if (type == ui::TextField::EventType::INSERT_TEXT || type == ui::TextField::EventType::DELETE_BACKWARD) {
            auto textField = dynamic_cast<ui::TextField*>(sender);
            std::string nickname = textField->getString();
            std::string text = GBKToUTF8::getString("��ӭ�㣡") + nickname;
            promptLabel->setString(text);
        }
        });

    // ������ť
    auto startButton = HoverButton::create("../Resources/Buttons/StartDefaultButton.png",
        "../Resources/Buttons/StartHoverButton.png",
        "../Resources/Buttons/StartActiveButton.png");

    // ���ð�ťλ��
    startButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + INITIAL_SCENE_BUTTON_OFFSET_Y));

    // ����һ����ʾ
    auto nameLabel = Label::createWithTTF(GBKToUTF8::getString("��Ϸ�ǳƲ���Ϊ��"), "../Resources/Fonts/FZZGY_J_EB.ttf", INITIAL_SCENE_FONT_SIZE);
    nameLabel->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABLES_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_NAME_LABLE_OFFSET_Y));
    nameLabel->setVisible(false);
    nameLabel->setTextColor(Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(nameLabel);

    // Ϊ��ť����¼�������
    startButton->addTouchEventListener([this, textField, nameLabel](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            std::string nickname = textField->getString();
            if (!nickname.empty()) {
                UserDefault::getInstance()->setStringForKey("PlayerName", nickname);
                UserDefault::getInstance()->flush();
                Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_DURATION, MenuScene::createScene(), Color3B::WHITE));
            }
            else {
                nameLabel->setVisible(true);
                this->scheduleOnce([nameLabel](float dt) {nameLabel->setVisible(false); }, PROMPT_MESSAGE_DURATION, "HidePromptLabel");
            }
        }
        });

    // ����ť��ӵ�������
    this->addChild(startButton);

    return true;
}