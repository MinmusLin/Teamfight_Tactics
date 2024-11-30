/****************************************************************
 * Project Name:  Teamfight_Tactic
 * File Name:     InitialScene.cpp
 * File Function: InitialScene���ʵ��
 * Author:        �ּ��ꡢ������
 * Update Date:   2023/12/31
 * License:       MIT License
 ****************************************************************/

#include <locale>
#include <codecvt>
#include "InitialScene.h"
#include "SelectionScene.h"
#include "Button/HoverButton.h"
#include "proj.win32/Constant.h"
#include "proj.win32/AudioPlayer.h"

// �����ռ�
using cocos2d::Scene;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;

// ����ǳ�
std::string g_PlayerName = "";

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
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/InitialScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    // �����ı���
    auto textField = cocos2d::ui::TextField::create(u8"������������Ϸ�ǳ�", "../Resources/Fonts/DingDingJinBuTi.ttf", INITIAL_SCENE_FONT_SIZE);
    textField->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABELS_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_TEXTFIELD_OFFSET_Y));
    textField->setMaxLength(NICKNAME_MAX_LENGTH);
    textField->setMaxLengthEnabled(true);
    textField->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(textField);

    // ������ǩ
    auto promptLabel = Label::createWithTTF("", "../Resources/Fonts/DingDingJinBuTi.ttf", INITIAL_SCENE_FONT_SIZE);
    promptLabel->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABELS_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_PROMPT_LABEL_OFFSET_Y));
    promptLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(promptLabel);

    // Ϊ�ı�������¼�������
    textField->addEventListener([promptLabel](Ref* sender, cocos2d::ui::TextField::EventType type) {
        if (type == cocos2d::ui::TextField::EventType::INSERT_TEXT || type == cocos2d::ui::TextField::EventType::DELETE_BACKWARD) {
            auto textField = dynamic_cast<cocos2d::ui::TextField*>(sender);
            std::string nickname = textField->getString();
            std::string text = u8"��ӭ�㣡" + nickname;
            promptLabel->setString(text);
        }
        });

    // ������ť
    auto startButton = HoverButton::create("../Resources/Buttons/InitialSceneButtons/StartDefaultButton.png",
        "../Resources/Buttons/InitialSceneButtons/StartHoverButton.png",
        "../Resources/Buttons/InitialSceneButtons/StartActiveButton.png");

    // ���ð�ťλ��
    startButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + INITIAL_SCENE_BUTTON_OFFSET_Y));

    // ����һ����ʾ
    auto nameLabel = Label::createWithTTF("", "../Resources/Fonts/DingDingJinBuTi.ttf", INITIAL_SCENE_FONT_SIZE);
    nameLabel->setPosition(Vec2(screenSize.width / 2 + INITIAL_SCENE_LABELS_OFFSET_X, screenSize.height / 2 + INITIAL_SCENE_NAME_LABEL_OFFSET_Y));
    nameLabel->setVisible(false);
    nameLabel->setTextColor(cocos2d::Color4B(DARK_BLUE_R, DARK_BLUE_G, DARK_BLUE_B, 255));
    this->addChild(nameLabel);

    // Ϊ��ť����¼�������
    startButton->addTouchEventListener([this, textField, nameLabel](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            // ���ص����Ч
            audioPlayer("../Resources/Music/ClickSoundEffect.mp3", false);

            std::string nickname = textField->getString();
            if (nickname.empty()) {
                nameLabel->setString(u8"��Ϸ�ǳƲ���Ϊ��");
                nameLabel->setVisible(true);
                this->scheduleOnce([nameLabel](float dt) {
                    nameLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "HideEmptyPromptLabel");
            }
            else if (!isValidString(nickname)) {
                nameLabel->setString(u8"��Ϸ�ǳƴ��ڷǷ��ַ�");
                nameLabel->setVisible(true);
                this->scheduleOnce([nameLabel](float dt) {
                    nameLabel->setVisible(false);
                    }, PROMPT_MESSAGE_DURATION, "HideInvalidPromptLabel");
            }
            else {
                g_PlayerName = nickname; // g_PlayerName �ڲ��洢����Ϊ UTF-8
                cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, SelectionScene::createScene(), cocos2d::Color3B::WHITE));
            }
        }
        });

    // ����ť��ӵ�������
    this->addChild(startButton);

    return true;
}

// ����ַ��Ϸ���
bool InitialScene::isValidCharacter(const char32_t ch)
{
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
        return true;
    }
    if (ch >= '0' && ch <= '9') {
        return true;
    }
    if ((ch >= 0x4E00 && ch <= 0x9FFF) || (ch >= 0x3400 && ch <= 0x4DBF)) {
        return true;
    }
    return false;
}

// ����ַ����Ϸ���
bool InitialScene::isValidString(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::u32string utf32str = converter.from_bytes(str);
    for (auto ch : utf32str) {
        if (!isValidCharacter(ch)) {
            return false;
        }
    }
    return true;
}